#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "../../clock/clock.h"
#include "../../buffer/buffer.h"

class Stearing {
public:
    Stearing(std::string filePath, std::shared_ptr<Clock> clock, SensorType key, std::shared_ptr<Buffer> buffer);
    std::function<void()> run();
    void readStearingLine();
    void fineNearestTime(double clock_time);
    
private:
    int index;
    std::string filePath;
    double steeringValue, time_stamp;
    SensorType key;
    std::shared_ptr<Clock> clock;
    std::shared_ptr<Buffer> buffer;
};
