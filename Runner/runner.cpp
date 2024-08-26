#include "runner.h"

Runner::Runner() {
	createFeatures();
	createDataObjects();
	addDataObjectsToBuffer();
}


std::function<void()> Runner::createThreads() {
        return [this]() {
            std::thread frontCameraThread(frontCamera->run());
            std::thread backCameraThread(backCamera->run());
            std::thread leftCameraThread(leftCamera->run());
            std::thread rightCameraThread(rightCamera->run());
            std::thread gpsThread(gps->run());
            std::thread imuThread(imu->run());
            std::thread steeringThread(stearing->run());
            std::thread speedThread(speed->run());
            std::thread throttleThread(throttle->run());
            std::thread brakeThread(brake->run());
            std::thread clockThread(clock->update_base_time());
            
            frontCameraThread.join();
            backCameraThread.join();
            leftCameraThread.join();
            rightCameraThread.join();
            gpsThread.join();
            imuThread.join();
            steeringThread.join();
            speedThread.join();
            throttleThread.join();
            brakeThread.join();
            clockThread.join();
        };
}

double Runner::findInitialTime(int index){
       namespace fs = std::filesystem; // Namespace alias for filesystem
       std::vector<std::string> filenames;
	
       // Iterate through the directory and collect JPEG filenames
       for (const auto& entry : fs::directory_iterator("../Data/3d_images/front")) {
		if (entry.path().extension() == ".jpeg") {
	            filenames.push_back(entry.path().string());
	        }
	}
	
	// Sort filenames alphabetically (or based on your requirement)
	std::sort(filenames.begin(), filenames.end());
	
	// Find the position of the last '/' or '\' (in case of Windows paths)
    	size_t lastSlash = filenames.at(index).find_last_of("/\\");
    	std::string nameWithExtension;
    
    	if (lastSlash != std::string::npos) {
        	// Extract the filename with extension
        	nameWithExtension = filenames.at(index).substr(lastSlash + 1);
    	} else {
    		// If there's no slash, assume the entire string is the filename
        	nameWithExtension = filenames.at(index);
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

void Runner::createFeatures() {
	this->buffer = std::make_shared<Buffer>();
	double initialTime = findInitialTime(0);
	double intervale = findClockIntervale();
	this->clock = std::make_shared<Clock>(initialTime, intervale);
	this->frontCamera = std::make_shared<Camera>("../Data/3d_images/front",
		 clock,SensorType::FrontCamera,buffer);
	this->backCamera = std::make_shared<Camera>("../Data/3d_images/back",
		 clock,SensorType::BackCamera,buffer);
	this->leftCamera = std::make_shared<Camera>("../Data/3d_images/left",
		 clock,SensorType::LeftCamera,buffer);
	this->rightCamera = std::make_shared<Camera>("../Data/3d_images/right",
		 clock,SensorType::RightCamera,buffer);
	this->gps = std::make_shared<GPS>("../Data/gps.csv", clock, SensorType::GPS, buffer);
	this->imu = std::make_shared<IMU>("../Data/imu.csv", clock, SensorType::IMU, buffer);
	this->speed = std::make_shared<Speed>("../Data/speed.csv", clock, SensorType::Speed,
		 buffer);
	this->stearing = std::make_shared<Stearing>("../Data/steering.csv", 
		clock, SensorType::Steering, buffer);
	this->throttle = std::make_shared<Throttle>("../Data/throttle.csv",
		clock,SensorType::Throttle,buffer);
	this->brake = std::make_shared<Brake>("../Data/brake.csv", clock, SensorType::Brake,
		buffer);
}

void Runner::createDataObjects() {
	this->frontCameraData = std::make_shared<CameraData>();
	this->backCameraData = std::make_shared<CameraData>();
	this->leftCameraData = std::make_shared<CameraData>();
	this->rightCameraData = std::make_shared<CameraData>();
	this->gpsData = std::make_shared<GPSData>();
	this->imuData = std::make_shared<IMUData>();
	this->stearingData = std::make_shared<StearingData>();
	this->speedData = std::make_shared<SpeedData>();
	this->throttleData = std::make_shared<ThrottleData>();
	this->brakeData = std::make_shared<BrakeData>();	
}

void Runner::addDataObjectsToBuffer() {
	buffer->addDataSource(SensorType::FrontCamera, frontCameraData);
	buffer->addDataSource(SensorType::BackCamera, backCameraData);
	buffer->addDataSource(SensorType::LeftCamera, leftCameraData);
	buffer->addDataSource(SensorType::RightCamera, rightCameraData);
	buffer->addDataSource(SensorType::GPS, gpsData);
	buffer->addDataSource(SensorType::IMU, imuData);
	buffer->addDataSource(SensorType::Speed, speedData);
	buffer->addDataSource(SensorType::Steering, stearingData);
	buffer->addDataSource(SensorType::Throttle, throttleData);
	buffer->addDataSource(SensorType::Brake, brakeData);
}

std::shared_ptr<Buffer> Runner::getBuffer(){
	return this->buffer;
}

double Runner::findClockIntervale() {
	double time1 = findInitialTime(0);
	double time2 = findInitialTime(1);
	
	return (time2 - time1);
}

