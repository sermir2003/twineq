#pragma once
#include <vector>
#include "task.h"
#include <chrono>
#include "integrators.h"

class Solver {
private:
    Task data_;
    std::vector<double> f_;
    std::vector<double> c_;
    std::vector<double> c_next_;
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time_;
    std::unique_ptr<Integrator> integrator_;

private:
    void PerformCalculation();  // Probably should be turned off from the constructor
    void ConstructFunction();
    void SaveResults();
    void InitProgress();
    void UpdateProgress(double progress);
    void CompleteProgress();

public:
    friend Integrator;
    friend ColumnMethod;
    friend TrapezoidMethod;
    friend SimpsonsMethod;
    Solver(Task&& problem);
};
