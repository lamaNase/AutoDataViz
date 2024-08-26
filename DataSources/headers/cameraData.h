#pragma once

#include <opencv2/opencv.hpp>
#include "dataSource.h"

class CameraData : public DataSource {
private:
    cv::Mat frame;

public:
    void updateData(const std::any& data) override;
    std::any getData() const override;
};


