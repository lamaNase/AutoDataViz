#pragma once

#include "dataSource.h"

class BrakeData : public DataSource {
private:
    double brakeValue;

public:
    void updateData(const std::any& data) override;
    std::any getData() const override;
};
