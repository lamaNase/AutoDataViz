#include "../headers/imu.h"

IMU::IMU(std::string filePath, std::shared_ptr<Clock> clock, SensorType key, std::shared_ptr<Buffer> buffer) {
	this->filePath = filePath;
	this->clock = clock;
	this->buffer = buffer;
	this->key = key;
	this-> index = 1;
}

std::function<void()> IMU::run() {
	return [this]() {
		double previous = 0;
		while (true) {	
			double now = clock->now();
			if (now != previous) {
			    fineNearestTime(now);
			    std::array<std::array<double, 3>, 3> data;
			    data[0] = accelerations;
			    data[1] = gyroscopic;
			    data[2] = magnayic;
			    buffer->updateDataSource(key, data);
			}
			previous = now;
		}
		
	};
}

void IMU::readIMULine() {
    std::ifstream file(filePath);
    std::string line;
    int currentLine = 0;

    // Open the file
    if (file.is_open()) {
        // Read lines until the specified index
        while (std::getline(file, line)) {
            if (currentLine == index) {
                std::stringstream ss(line);
                std::string x_acc, y_acc, z_acc, time;
                std::string x_gyro, y_gyro, z_gyro;
                std::string x_mag, y_mag, z_mag;

                // Split the line using comma as the delimiter
                std::getline(ss, time, ',');
                std::getline(ss, x_acc, ',');
                std::getline(ss, y_acc, ',');
                std::getline(ss, z_acc, ',');
                
                accelerations[0] = std::stod(x_acc);
                accelerations[1] = std::stod(y_acc);
                accelerations[3] = std::stod(z_acc);
                this->time_stamp = std::stod(time);
                
                for (int i = 0; i < 6; i++)
                	std::getline(ss, time, ',');
                
                std::getline(ss, x_gyro, ',');
                std::getline(ss, y_gyro, ',');
                std::getline(ss, z_gyro, ',');
                
                gyroscopic[0] = std::stod(x_gyro);
                gyroscopic[1] = std::stod(y_gyro);
                gyroscopic[2] = std::stod(z_gyro);
                
                
                for (int i = 0; i < 3; i++)
                	std::getline(ss, time, ',');
                
                std::getline(ss, x_mag, ',');
                std::getline(ss, y_mag, ',');
                std::getline(ss, z_mag, ',');
                
                magnayic[0] = std::stod(x_mag);
                magnayic[1] = std::stod(y_mag);
                magnayic[2] = std::stod(z_mag);
                
                break;
            }
            currentLine++;
        }
        file.close();
    } else {
        std::cerr << "Unable to open file" << std::endl;
    }
}


void IMU::fineNearestTime(double clock_time) {
    readIMULine();
    while(time_stamp < clock_time) {
    	index++;
    	readIMULine();
    }
    if (index == 1){
    	readIMULine();
    	return;
    }
    index--;
    readIMULine();
}



