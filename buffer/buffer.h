#pragma once

#include <map>
#include <memory>
#include <string>
#include <mutex>
#include <iostream>
#include <fstream> 
#include <sstream> 
#include "../DataSources/headers/dataSource.h"
#include "../sensorType.h"

class Buffer {
private:
    // Map to store DataSource objects
    std::map<SensorType, std::shared_ptr<DataSource>> dataSources;
    // Map to store mutexes for each DataSource
    std::map<SensorType, std::mutex> dataSourceMutexes;

public:
    // Add a DataSource to the buffer
    void addDataSource(const SensorType key, std::shared_ptr<DataSource> dataSource) {
        std::lock_guard<std::mutex> lock(getMutex(key));
        dataSources[key] = dataSource;
    }

    // Update the data in a DataSource in the buffer
    void updateDataSource(const SensorType key, const std::any& data) {
        std::lock_guard<std::mutex> lock(getMutex(key));
        auto it = dataSources.find(key);
        if (it != dataSources.end()) {
            auto dataSource = it->second;
            if (dataSource) {
                dataSource->updateData(data);
            } else {
                std::cerr << "No DataSource found for key: " << static_cast<int>(key) << std::endl;
            }
        } else {
            std::cerr << "No DataSource found for key: " << static_cast<int>(key) << std::endl;
        }
    }

    // Retrieve the data from a DataSource in the buffer
    template<typename T>
    std::shared_ptr<const T> getDataSource(const SensorType key) {
        std::lock_guard<std::mutex> lock(getMutex(key));
        auto it = dataSources.find(key);
        if (it != dataSources.end()) {
            auto dataSource = std::dynamic_pointer_cast<const T>(it->second);
            if (dataSource) {
                return dataSource;
            } else {
                std::cerr << "Type mismatch for key: " << static_cast<int>(key) << std::endl;
            }
        } else {
            std::cerr << "No DataSource found for key: " << static_cast<int>(key) << std::endl;
        }
        return nullptr; // Return nullptr if the type does not match or key is not found
    }

private:
    std::mutex& getMutex(const SensorType key) {
        auto [it, inserted] = dataSourceMutexes.try_emplace(key);
        return it->second;
    }
};

