#include "../headers/cameraData.h"

void CameraData::updateData(const std::any& data) {
    try {
        frame = std::any_cast<cv::Mat>(data);
    } catch (const std::bad_any_cast& e) {
        throw std::runtime_error("Failed to cast std::any to cv::Mat: " +
        		 std::string(e.what()));
    }
}

std::any CameraData::getData() const {
    return frame;
}
