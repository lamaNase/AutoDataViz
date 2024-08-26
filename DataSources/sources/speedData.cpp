#include "../headers/speedData.h"

void SpeedData::updateData(const std::any& data) {
	try {
		this->speed = std::any_cast<double>(data);
    	} catch (const std::bad_any_cast& e) {
        	throw std::runtime_error("Failed to cast std::any to double: " +
        		 std::string(e.what()));
    	}
}

std::any SpeedData::getData() const {
	return this->speed;
}
