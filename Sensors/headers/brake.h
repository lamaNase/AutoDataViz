#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "../../clock/clock.h"
#include "../../buffer/buffer.h"

class Brake {
public:
    Brake(std::string filePath, std::shared_ptr<Clock> clock, SensorType key, std::shared_ptr<Buffer> buffer);
    std::function<void()> run();
    void readBrakeLine();
    void fineNearestTime(double clock_time);
    
private:
    int index;
    double time_stamp, brakeValue;
    std::string filePath;
    SensorType key;
    std::shared_ptr<Clock> clock;
    std::shared_ptr<Buffer> buffer;
};
