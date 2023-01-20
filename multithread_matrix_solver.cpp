#include "multithread_matrix_solver.h"
#include <fstream>
#include <iostream>
#include <iomanip>

MultithreadingMatrixSolver::MultithreadingMatrixSolver(Task&& task)
    : data_(std::move(task)),
      f_(data_.grid_count()),
      c_(data_.grid_count()),
      c_tmp_with_false_sharing_(data_.grid_count()),
      matrix_((data_.grid_count() + 1) / 2 * data_.grid_count()),
      mutexes_(task.NumberOfThreads()) {
    cnt_operating_.store(0);
    uint64_t seg_size = (data_.grid_count() + data_.NumberOfThreads() - 1) / data_.NumberOfThreads();
    for (size_t i = 0; i < data_.NumberOfThreads(); ++i) {
        size_t left = std::max(2ul, seg_size * i);
        size_t right = std::min(seg_size * (i + 1), data_.grid_count());
        workers_.emplace_back(MultithreadingMatrixSolver::MulPerformer, i, left, right);
    }
    ConstructFunction();
    if (data_.IntegrationMethod() == "Column") {
        ConstructMatrixColumn();
    } else {
        std::cout
            << "Other integration methods have not yet been implemented for a solver using matrices"
            << std::endl;
        exit(0);
    }
    PerformCalculation();
}
void MultithreadingMatrixSolver::ConstructFunction() {
    std::cout << "Construct function..." << std::endl;
    double x = -data_.r();
    for (size_t i = 0; i < (data_.grid_count() + 1) / 2; ++i) {
        f_[i] = (data_.N() * data_.m(x) - data_.s() * data_.w(x)) /
                (data_.b() + data_.s() * data_.w(x));
        f_[data_.grid_count() - i - 1] = f_[i];
        x += data_.step_size();
    }
    std::cout << "Construct function --- Done!" << std::endl;
}
void MultithreadingMatrixSolver::ConstructMatrixColumn() {
    std::cout << "Construct matrix using Column integration method..." << std::endl;
    double x = -data_.r();
    for (size_t i = 0; i < (data_.grid_count() + 1) / 2; ++i) {
        double y = -data_.r();
        for (size_t j = 0; j < data_.grid_count(); ++j) {
            matrix_[i * data_.grid_count() + j] =
                ((j == 0 || j == data_.iter_count() - 1) ? 0.5 : 1) * data_.step_size() *
                data_.b() / (data_.b() + data_.s() * data_.w(x)) * data_.m(x - y);
            y += data_.step_size();
        }
        x += data_.step_size();
    }
    std::cout << "Construct matrix --- Done!" << std::endl;
}
void MultithreadingMatrixSolver::MulPerformer(size_t inner_id, size_t left, size_t right) {
    while (true) {
        mutexes_[inner_id].lock();
        for (size_t i = left; i < right; ++i) {
            c_tmp_with_false_sharing_[i] = 0;
            for (size_t j = 0; j < data_.grid_count(); ++j) {
                c_tmp_with_false_sharing_[i] += matrix_[i * data_.grid_count() + j] * c_[j];
            }
            c_tmp_with_false_sharing_[data_.grid_count() - i - 1] = c_tmp_with_false_sharing_[i];
        }
        cnt_operating_.fetch_sub(1);
    }
}
void MultithreadingMatrixSolver::MultiplyMatrixByVector() {
    for (size_t i = 0; i < (data_.grid_count() + 1) / 2; ++i) {
        c_next_[i] = 0;
        for (size_t j = 0; j < data_.grid_count(); ++j) {
            c_next_[i] += matrix_[i * data_.grid_count() + j] * c_[j];
        }
        c_next_[data_.grid_count() - i - 1] = c_next_[i];
    }
}
void MultithreadingMatrixSolver::PerformCalculation() {
    ProgressCounter calc_progress("Calculation");
    for (size_t i = 0; i < data_.grid_count(); ++i) {
        c_[i] = f_[i];
    }
    for (size_t iteration = 1; iteration < data_.iter_count(); ++iteration) {
        MultiplyMatrixByVector();
        for (size_t i = 0; i < data_.grid_count(); ++i) {
            c_next_[i] += f_[i];
        }
        std::swap(c_, c_next_);
        calc_progress.UpdateProgress(1.0 * iteration / data_.iter_count());
    }
    calc_progress.FinishAction();
    SaveResults();
}
void MultithreadingMatrixSolver::SaveResults() {
    std::ofstream file(data_.PathToResFile(), std::ios::out);
    double x = -data_.r();
    for (size_t i = 0; i < data_.grid_count(); ++i) {
        file << std::fixed << std::setprecision(9) << x << " " << c_[i] << std::endl;
        x += data_.step_size();
    }
}
