#pragma once

#include "dataSource.h"

class StearingData : public DataSource {
private:
    double stearing;

public:
    void updateData(const std::any& data) override;
    std::any getData() const override;
};
