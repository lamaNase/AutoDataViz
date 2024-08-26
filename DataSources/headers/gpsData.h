#pragma once

#include "dataSource.h"
#include <utility> // For std::pair
#include <any>

class GPSData : public DataSource {
private:
    double latitude;
    double longitude;

public:
    void updateData(const std::any& data) override;
    std::any getData() const override;
};
