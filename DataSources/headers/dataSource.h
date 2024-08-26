#pragma once

#include <any>
#include <stdexcept>

class DataSource {
public:
    virtual ~DataSource() {}

    virtual void updateData(const std::any& data) = 0;
    virtual std::any getData() const = 0;
};

