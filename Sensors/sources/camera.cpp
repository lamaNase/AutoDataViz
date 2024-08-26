#include "../headers/camera.h"

Camera::Camera(std::string folderPath, std::shared_ptr<Clock> clock, SensorType key, std::shared_ptr<Buffer> buffer) {
	this->key = key;
	this->folderPath = folderPath;
	this->clock = clock;
	this->buffer = buffer;
	this->index = 0;
	paths = sortImages();
}

std::function<void()> Camera::run() {
	return [this]() {
		double previous = 0;
		while (true) {
			double now = clock->now();
			if (now != previous) {
			    fineNearestTime(now);
			    buffer->updateDataSource(key, cv::imread(paths.at(index)));
			}
			previous = now;
		}
	};
}

std::vector<std::string> Camera::sortImages() {
    namespace fs = std::filesystem; // Namespace alias for filesystem
    std::vector<std::string> filenames;

    // Iterate through the directory and collect JPEG filenames
    for (const auto& entry : fs::directory_iterator(this->folderPath)) {
        if (entry.path().extension() == ".jpeg") {
            filenames.push_back(entry.path().string());
        }
    }

    // Sort filenames alphabetically (or based on your requirement)
    std::sort(filenames.begin(), filenames.end());
    return filenames;
}

double Camera::getTime() {
	// Find the position of the last '/' or '\' (in case of Windows paths)
    	size_t lastSlash = this->paths.at(index).find_last_of("/\\");
    	std::string nameWithExtension;
    
    	if (lastSlash != std::string::npos) {
        	// Extract the filename with extension
        	nameWithExtension = this->paths.at(index).substr(lastSlash + 1);
    	} else {
    		// If there's no slash, assume the entire string is the filename
        	nameWithExtension = this->paths.at(index);
    	}

    	// Find the position of the last '.' before the extension
    	size_t lastDot = nameWithExtension.find_last_of('.');
    
    	if (lastDot != std::string::npos) {
    		// Extract the numeric part (before the extension)
        	std::string numericPart = nameWithExtension.substr(0, lastDot);
        	// Convert the numeric part to a double
        	return std::stod(numericPart);
    	}

    	// If no valid numeric part was found, throw an error or handle as needed
    	throw std::invalid_argument("No valid number found in the filename");
}

void Camera::fineNearestTime(double clock_time) {
    while(getTime() < clock_time)
    	index++;
    
    if (index == 0)
    	return;
    
    index--;
}

