#include "../headers/stearing.h"

Stearing::Stearing(std::string filePath, std::shared_ptr<Clock> clock, SensorType key, std::shared_ptr<Buffer> buffer) {
	this->filePath = filePath;
	this->clock = clock;
	this->buffer = buffer;
	this->key = key;
	this-> index = 1;
}

std::function<void()> Stearing::run() {
	return [this]() {
		double previous = 0;
		while (true) {	
			double now = clock->now();
			if (now != previous) {
			    fineNearestTime(now);
			    buffer->updateDataSource(key, steeringValue);
			}
			previous = now;
		}
		
	};
}

void Stearing::readStearingLine() {
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
                
                steeringValue = std::stod(value);
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

void Stearing::fineNearestTime(double clock_time) {
    readStearingLine();
    while(time_stamp < clock_time) {
    	index++;
    	readStearingLine();
    }
    if (index == 1){
    	readStearingLine();
    	return;
    }
    index--;
    readStearingLine();
}

