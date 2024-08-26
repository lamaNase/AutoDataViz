#include "../headers/brake.h"

Brake::Brake(std::string filePath, std::shared_ptr<Clock> clock, SensorType key, std::shared_ptr<Buffer> buffer) {
	this->filePath = filePath;
	this->clock = clock;
	this->buffer = buffer;
	this->key = key;
	this-> index = 1;
}

std::function<void()> Brake::run() {
	return [this]() {
		double previous = 0;
		while (true) {	
			double now = clock->now();
			if (now != previous) {
			    fineNearestTime(now);
			    buffer->updateDataSource(key, brakeValue);
			}
			previous = now;
		}
		
	};
}

void Brake::readBrakeLine() {
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
                
                brakeValue = std::stod(value);
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

void Brake::fineNearestTime(double clock_time) {
    readBrakeLine();
    while(time_stamp < clock_time) {
    	index++;
    	readBrakeLine();
    }
    if (index == 1){
    	readBrakeLine();
    	return;
    }
    index--;
    readBrakeLine();
}
