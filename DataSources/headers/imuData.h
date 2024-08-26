#pragma once

#include <array>
#include "dataSource.h"

class IMUData : public DataSource {
public:
    void updateData(const std::any& data) override;
    std::any getData() const override;
    
private:
    // index 0 represents x-axis, index 1 y axis and index 2 z axis
    std::array<double, 3> accelerations;
    std::array<double, 3> gyroscopic;
    std::array<double, 3> magnetic;
};

