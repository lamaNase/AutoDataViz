#pragma once

#include "dataSource.h"

class SpeedData : public DataSource {
private:
    double speed;

public:
    void updateData(const std::any& data) override;
    std::any getData() const override;
};
