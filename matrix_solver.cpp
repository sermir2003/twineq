#include "matrix_solver.h"
#include <iostream>

SimpleMatrixSolver::SimpleMatrixSolver(Task&& task)
    : data_(std::move(task)),
      f_(data_.grid_count()),
      c_(data_.grid_count()),
      c_next_(data_.grid_count()),
      matrix_((data_.grid_count() + 1) / 2 * data_.grid_count()) {
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
void SimpleMatrixSolver::ConstructFunction() {
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
void SimpleMatrixSolver::ConstructMatrixColumn() {
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
void SimpleMatrixSolver::MultiplyMatrixByVector() {
    for (size_t i = 0; i < (data_.grid_count() + 1) / 2; ++i) {
        c_next_[i] = 0;
        for (size_t j = 0; j < data_.grid_count(); ++j) {
            c_next_[i] += matrix_[i * data_.grid_count() + j] * c_[j];
        }
        c_next_[data_.grid_count() - i - 1] = c_next_[i];
    }
}
void SimpleMatrixSolver::PerformCalculation() {
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
    data_.SaveResults(c_);
}
