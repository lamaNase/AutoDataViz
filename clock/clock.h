#pragma once

#include <iostream>
#include <iomanip>
#include <mutex>
#include <iomanip>
#include <functional>
#include <thread>

class Clock {
public:
    Clock(double initial_time_seconds, double intervale);

    // Get the current time
    double now() const;

    // Update the base time (increment by 1 microsecond)
    std::function<void()> update_base_time();

private:
    double current_time; 
    double intervale;
    mutable std::mutex clockMutex; // mutable to allow locking in const methods
};

