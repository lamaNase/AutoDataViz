#pragma once

#include <iostream>
#include <string>
#include <iomanip>
#include <memory>
#include <thread>
#include "../buffer/buffer.h"
#include "../clock/clock.h"
#include "../Sensors/headers/headers.h"
#include "../DataSources/headers/headers.h"

class Runner {
private:
	std::shared_ptr<Clock> clock;
	std::shared_ptr<Buffer> buffer;
	std::shared_ptr<Camera> frontCamera;
	std::shared_ptr<Camera> backCamera;
	std::shared_ptr<Camera> leftCamera;
	std::shared_ptr<Camera> rightCamera;
	std::shared_ptr<GPS> gps;
	std::shared_ptr<IMU> imu;
	std::shared_ptr<Stearing> stearing;
	std::shared_ptr<Speed> speed;
	std::shared_ptr<Throttle> throttle;
	std::shared_ptr<Brake> brake;

	std::shared_ptr<DataSource> frontCameraData;
	std::shared_ptr<DataSource> backCameraData;
	std::shared_ptr<DataSource> leftCameraData;
	std::shared_ptr<DataSource> rightCameraData;
	std::shared_ptr<DataSource> gpsData;
	std::shared_ptr<DataSource> imuData;
	std::shared_ptr<DataSource> stearingData;
	std::shared_ptr<DataSource> speedData;
	std::shared_ptr<DataSource> throttleData;
	std::shared_ptr<DataSource> brakeData;
	
public:
	Runner();
	std::function<void()> createThreads();
	double findInitialTime(int index);
	void createFeatures();
	void createDataObjects();
	void addDataObjectsToBuffer();
	std::shared_ptr<Buffer> getBuffer();
	double findClockIntervale();
};
