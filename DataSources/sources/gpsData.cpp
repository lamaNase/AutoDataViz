#include "../headers/gpsData.h"

void GPSData::updateData(const std::any& data) {
        try {
        	auto gpsData = std::any_cast<std::pair<double, double>>(data);
        	latitude = gpsData.first;
        	longitude = gpsData.second;
        } catch (const std::bad_any_cast& e) {
        	throw std::runtime_error("Failed to cast std::any to std::pair: " +
        		 std::string(e.what()));
    }
}

std::any GPSData::getData() const {
        return std::make_pair(latitude, longitude);
}
