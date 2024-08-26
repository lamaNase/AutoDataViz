#include "../headers/gps.h"

GPS::GPS(std::string filePath, std::shared_ptr<Clock> clock, SensorType key, std::shared_ptr<Buffer> buffer) {
	this->filePath = filePath;
	this->clock = clock;
	this->buffer = buffer;
	this->key = key;
	this->index = 1;
}

std::function<void()> GPS::run() {
	return [this]() {
		double previous = 0;
		while (true) {	
			double now = clock->now();
			if (now != previous) {
			    fineNearestTime(now);
			    buffer->updateDataSource(key, std::make_pair(latitude,longitude));
			}
			previous = now;
		}
	};
}

void GPS::readGPSLine() {
    std::ifstream file(filePath);
    std::string line;
    int currentLine = 0;

    // Open the file
    if (file.is_open()) {
        // Read lines until the specified index
        while (std::getline(file, line)) {
            if (currentLine == index) {
                std::stringstream ss(line);
                std::string lat,longi, time;

                // Split the line using comma as the delimiter
                std::getline(ss, time, ',');
                std::getline(ss, lat, ',');
                std::getline(ss, longi, ',');
                
                latitude = std::stod(lat);
                longitude = std::stod(longi);
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

void GPS::fineNearestTime(double clock_time) {
    readGPSLine();
    while(time_stamp < clock_time) {
    	index++;
    	readGPSLine();
    }
    if (index == 1){
    	readGPSLine();
    	return;
    }
    index--;
    readGPSLine();
}


