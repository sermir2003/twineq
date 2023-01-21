#pragma once
#include <vector>
#include "task.h"
#include "integrators.h"
#include "progress_counter.h"

class SimpleMatrixSolver {
private:
    Task data_;
    std::vector<double> f_;
    std::vector<double> c_;
    std::vector<double> c_next_;
    std::vector<double> matrix_;
private:
    void PerformCalculation();  // Probably should be turned off from the constructor
    void ConstructFunction();
    void ConstructMatrixColumn();
    void MultiplyMatrixByVector();
public:
    SimpleMatrixSolver(Task&& task);
};
