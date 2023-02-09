#pragma once
#include <vector>
#include "task.h"
#include "integrators.h"
#include "progress_counter.h"

class SimpleMatrixSolver {
private:
    const Task& data_;
    std::vector<Real> f_;
    std::vector<Real> c_;
    std::vector<Real> c_next_;
    std::vector<Real> matrix_;
    std::string calculation_name_;

private:
    void ConstructFunction();
    void ConstructMatrixColumn();
    void PerformIteration();
    void SaveResults();

public:
    SimpleMatrixSolver(const Task& task, const std::string& calculation_name);
    std::vector<Real> PerformCalculation();
};
