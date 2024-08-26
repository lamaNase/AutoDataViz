#include "../headers/throttleData.h"

void ThrottleData::updateData(const std::any& data) {
	try {
		this->throttle = std::any_cast<double>(data);
	} catch (const std::bad_any_cast& e) {
        	throw std::runtime_error("Failed to cast std::any to double: " +
        		 std::string(e.what()));
    	}
}

std::any ThrottleData::getData() const {
	return throttle;
}
