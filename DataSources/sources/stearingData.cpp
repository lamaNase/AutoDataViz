#include "../headers/stearingData.h"

void StearingData::updateData(const std::any& data) {
	try {
		this->stearing = std::any_cast<double>(data);
	} catch (const std::bad_any_cast& e) {
        	throw std::runtime_error("Failed to cast std::any to double: " +
        		 std::string(e.what()));
    	}
}

std::any StearingData::getData() const {
	return this->stearing;
}
