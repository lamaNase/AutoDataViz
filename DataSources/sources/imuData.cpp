#include "../headers/imuData.h"

void IMUData::updateData(const std::any& data) {
        try {
        	auto imuData = std::any_cast<std::array<std::array<double, 3>, 3>>(data);
        	this->accelerations = imuData[0];
        	this->gyroscopic = imuData[1];
        	this->magnetic = imuData[2];
    	} catch (const std::bad_any_cast& e) {
        	throw std::runtime_error("Failed to cast std::any to std::array: " +
        		 std::string(e.what()));
    	}
}

std::any IMUData::getData() const {
        std::array<std::array<double, 3>, 3> imuArray;
        imuArray[0] = this->accelerations;
        imuArray[1] = this->gyroscopic;
        imuArray[2] = this->magnetic;
        return imuArray;
}
