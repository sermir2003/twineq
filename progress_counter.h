#pragma once
#include <chrono>
#include <string>
#include "real_number.h"

class ProgressCounter {
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time_;
    std::string action_name_;
public:
    ProgressCounter(const std::string& action_name);
    void UpdateProgress(Real progress);
    void FinishAction();
};
