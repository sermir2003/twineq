#pragma once
#include <vector>
#include "task.h"
#include "integrators.h"
#include "progress_counter.h"

class SimpleMatrixSolver {
private:
    const Task& data_;
    std::vector<double> f_;
    std::vector<double> c_;
    std::vector<double> c_next_;
    std::vector<double> matrix_;
    std::string calculation_name_;

private:
    void ConstructFunction();
    void ConstructMatrixColumn();
    void MultiplyMatrixByVector();
    void SaveResults();

public:
    SimpleMatrixSolver(const Task& task, const std::string& calculation_name);
    void PerformCalculation();
};
