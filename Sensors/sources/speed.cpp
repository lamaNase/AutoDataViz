#include "../headers/speed.h"

Speed::Speed(std::string filePath, std::shared_ptr<Clock> clock, SensorType key, std::shared_ptr<Buffer> buffer) {
	this->filePath = filePath;
	this->clock = clock;
	this->buffer = buffer;
	this->key = key;
	this-> index = 1;
}

std::function<void()> Speed::run() {
	return [this]() {
		double previous = 0;
		while (true) {	
			double now = clock->now();
			if (now != previous) {
			    fineNearestTime(now);
			    buffer->updateDataSource(key, speedValue);
			}
			previous = now;
		}
		
	};
}

void Speed::readSpeedLine() {
    std::ifstream file(filePath);
    std::string line;
    int currentLine = 0;

    // Open the file
    if (file.is_open()) {
        // Read lines until the specified index
        while (std::getline(file, line)) {
            if (currentLine == index) {
                std::stringstream ss(line);
                std::string value, time;

                // Split the line using comma as the delimiter
                std::getline(ss, time, ',');
                std::getline(ss, value, ',');
                
                speedValue = std::stod(value);
                time_stamp = std::stod(time);
                break;
            }
            currentLine++;
        }
        file.close();
    } else {
        std::cerr << "Unable to open file" << std::endl;
    }
}


void Speed::fineNearestTime(double clock_time) {
    readSpeedLine();
    while(time_stamp < clock_time) {
    	index++;
    	readSpeedLine();
    }
    if (index == 1){
    	readSpeedLine();
    	return;
    }
    index--;
    readSpeedLine();
}




