#pragma once

#include "dataSource.h"

class ThrottleData : public DataSource {
private:
    double throttle;

public:
    void updateData(const std::any& data) override;
    std::any getData() const override;
};
