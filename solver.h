#pragma once
#include <vector>
#include "problem.h"
#include <chrono>

class Solver {
private:
    Problem data_;
    std::vector<double> f_;
    std::vector<double> c_;
    std::vector<double> c_next_;
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time_;
private:
    void PerformCalculation();  // Probably should be turned off from the constructor
    void ConstructFunction();
    void SaveResults();
    void InitProgress();
    void UpdateProgress(double progress);
    void CompleteProgress();
public:
    Solver(Problem&& problem);
};
