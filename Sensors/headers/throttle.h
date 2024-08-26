#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "../../clock/clock.h"
#include "../../buffer/buffer.h"

class Throttle {
public:
    Throttle(std::string filePath, std::shared_ptr<Clock> clock, SensorType key, std::shared_ptr<Buffer> buffer);
    std::function<void()> run();
    void readThrottleLine();
    void fineNearestTime(double clock_time);
    
private:
    int index;
    double time_stamp, throttleValue;
    std::string filePath;
    SensorType key;
    std::shared_ptr<Clock> clock;
    std::shared_ptr<Buffer> buffer;
};
