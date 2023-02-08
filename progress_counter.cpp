#include "progress_counter.h"
#include <iostream>
#include <iomanip>
#include "real_number.h"

typedef std::chrono::time_point<std::chrono::high_resolution_clock> Time;

static const std::string kBleachingLine = "\r" + std::string(100, ' ') + '\r';

ProgressCounter::ProgressCounter(const std::string& action_name) : action_name_(action_name), enabled_(true) {
    std::cout << action_name_ << " has begun" << std::endl;
    std::cout << "Progress: 0%" << std::flush;
    start_time_ = std::chrono::high_resolution_clock::now();
}
void ProgressCounter::UpdateProgress(Real progress) {
    std::cout << kBleachingLine;
    Time cur_time = std::chrono::high_resolution_clock::now();
    auto delta =
        std::chrono::duration_cast<std::chrono::milliseconds>(cur_time - start_time_).count();
    auto time_left = 1.0 * delta / progress * (1 - progress);
    std::cout << "Progress: " << std::fixed << std::setprecision(2) << 100 * progress << "%"
              << "; time left: " << MillisecondsToFormat(time_left)
              << "; time used: " << MillisecondsToFormat(delta) << std::flush;
}
void ProgressCounter::FinishAction() {
    enabled_ = false;
    Time cur_time = std::chrono::high_resolution_clock::now();
    auto delta =
        std::chrono::duration_cast<std::chrono::milliseconds>(cur_time - start_time_).count();
    std::cout << kBleachingLine << "Progress: 100%"
              << "; time used: " << MillisecondsToFormat(delta)
              << std::endl;
    std::cout << action_name_ << " is completed" << std::endl;
}
std::string ProgressCounter::MillisecondsToFormat(uint64_t time) {
    time /= 1000;
    uint64_t seconds = time % 60;
    time /= 60;
    uint64_t minutes = time % 60;
    time /= 60;
    uint64_t hour = time;
    std::string result;
    if (hour) {
        result += std::to_string(hour) + "h ";
    }
    if (minutes) {
        result += std::to_string(minutes) + "m ";
    }
    result += std::to_string(seconds) + "s";
    return result;
}
ProgressCounter::~ProgressCounter() {
    if (enabled_) {
        FinishAction();
    }
}
