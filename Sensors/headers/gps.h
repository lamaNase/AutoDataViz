#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "../../clock/clock.h"
#include "../../buffer/buffer.h"

class GPS {
public:
    GPS(std::string filePath, std::shared_ptr<Clock> clock, SensorType key, std::shared_ptr<Buffer> buffer);
    std::function<void()> run();
    void readGPSLine();
    void fineNearestTime(double clock_time);
    
private:
    int index;
    double latitude,longitude, time_stamp;
    std::string filePath;
    SensorType key;
    std::shared_ptr<Clock> clock;
    std::shared_ptr<Buffer> buffer;
};
