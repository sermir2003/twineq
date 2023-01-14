#include "progress_counter.h"
#include <iostream>
#include <iomanip>

typedef std::chrono::time_point<std::chrono::high_resolution_clock> Time;

static const std::string kBleachingLine = "\r" + std::string(100, ' ') + '\r';

ProgressCounter::ProgressCounter(const std::string& action_name) : action_name_(action_name) {
    std::cout << action_name_ << " started" << std::endl;
    std::cout << "Progress: 0%" << std::flush;
    start_time_ = std::chrono::high_resolution_clock::now();
}
void ProgressCounter::UpdateProgress(double progress) {
    std::cout << kBleachingLine;
    Time cur_time = std::chrono::high_resolution_clock::now();
    auto delta =
        std::chrono::duration_cast<std::chrono::milliseconds>(cur_time - start_time_).count();
    auto time_left = 1.0 * delta / progress * (1 - progress);
    std::cout << "Progress: " << std::fixed << std::setprecision(1) << 100 * progress << "%"
              << "; time left: " << std::setprecision(0) << time_left / 1000 << " s"
              << "; time used: " << delta / 1000 << " s" << std::flush;
}
void ProgressCounter::FinishAction() {
    Time cur_time = std::chrono::high_resolution_clock::now();
    auto delta =
        std::chrono::duration_cast<std::chrono::milliseconds>(cur_time - start_time_).count();
    std::cout << kBleachingLine << "Progress: 100%"
              << "; time used: " << std::setprecision(0) << delta / 1000 << " s" << std::endl;
    std::cout << action_name_ << " finished" << std::endl;
}
