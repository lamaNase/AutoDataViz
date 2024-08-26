#pragma once

#include <iostream>
#include <opencv2/opencv.hpp>
#include <filesystem>
#include <algorithm>
#include <string>
#include <vector>
#include <memory>
#include <iomanip>
#include "../../clock/clock.h"
#include "../../buffer/buffer.h"

class Camera {
public:
    Camera(std::string folderPath,std::shared_ptr<Clock> clock,SensorType key, std::shared_ptr<Buffer> buffer);
    std::function<void()> run();
    std::vector<std::string> sortImages();
    double getTime();
    void fineNearestTime(double clock_time);
    
private:
    int index;
    std::string folderPath;
    SensorType key;
    std::vector<std::string> paths;
    std::shared_ptr<Clock> clock;
    std::shared_ptr<Buffer> buffer;
};
