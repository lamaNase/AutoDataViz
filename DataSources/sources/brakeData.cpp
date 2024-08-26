#include "../headers/brakeData.h"

void BrakeData::updateData(const std::any& data) {
	try {
		this->brakeValue = std::any_cast<double>(data);
	} catch (const std::bad_any_cast& e) {
        	throw std::runtime_error("Failed to cast std::any to double: " +
        		 std::string(e.what()));
    	}
}

std::any BrakeData::getData() const {
	return brakeValue;
}
