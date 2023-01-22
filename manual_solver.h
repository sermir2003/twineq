#pragma once
#include <vector>
#include "task.h"
#include "integrators.h"
#include "progress_counter.h"

class ManualSolver {
private:
    Task data_;
    std::vector<double> f_;
    std::vector<double> c_;
    std::vector<double> c_next_;
    std::unique_ptr<Integrator> integrator_;
    std::string calculation_name_;

private:
    void ConstructFunction();
    void SaveResults();

public:
    ManualSolver(Task&& task, const std::string& calculation_name);
    std::vector<double> PerformCalculation();  // Probably should be turned off from the constructor
};
