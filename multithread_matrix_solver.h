#pragma once
#include <vector>
#include <thread>
#include <mutex>
#include <atomic>
#include "task.h"
#include "integrators.h"
#include "progress_counter.h"

class MultithreadingMatrixSolver {
private:
    Task data_;
    std::vector<double> f_;
    std::vector<double> c_;
    std::vector<double> c_tmp_with_false_sharing_;
    std::vector<double> matrix_;
    std::vector<std::mutex> mutexes_;
    std::atomic<size_t> cnt_operating_;
    std::vector<std::jthread> workers_;
private:
    void PerformCalculation();  // Probably should be turned off from the constructor
    void ConstructFunction();
    void ConstructMatrixColumn();
    void MultiplyMatrixByVector();
    void MulPerformer(size_t inner_id, size_t left, size_t right);
    void SaveResults();
public:
    MultithreadingMatrixSolver(Task&& task);
};
