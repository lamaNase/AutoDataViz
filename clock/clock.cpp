#include "clock.h"

Clock::Clock(double initial_time_seconds, double intervale) {
	this->current_time = initial_time_seconds;
	this->intervale = intervale;
}

double Clock::now() const {
    std::lock_guard<std::mutex> lock(clockMutex);
    return current_time;
}

std::function<void()> Clock::update_base_time() {
    return [this]() {
    	int sleepIntervale = int(intervale * 1000);
    	while(true) {
    		std::this_thread::sleep_for(std::chrono::milliseconds(sleepIntervale));
    		std::lock_guard<std::mutex> lock(clockMutex);
    		current_time += intervale; 
    	}
    };
}

