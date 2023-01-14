#pragma once
#include <vector>
#include "task.h"
#include <chrono>
#include "integrators.h"
#include "progress_counter.h"

class ManualSolver {
private:
    Task data_;
    std::vector<double> f_;
    std::vector<double> c_;
    std::vector<double> c_next_;
    std::unique_ptr<Integrator> integrator_;
private:
    void PerformCalculation();  // Probably should be turned off from the constructor
    void ConstructFunction();
    void SaveResults();
public:
    friend Integrator;
    friend ColumnMethod;
    friend TrapezoidMethod;
    friend SimpsonsMethod;
    ManualSolver(Task&& problem);
};
