#include "matrix_solver.h"
#include <fstream>
#include <iostream>
#include <iomanip>

SimpleMatrixSolver::SimpleMatrixSolver(const Task& task, const std::string& calculation_name)
    : data_(task),
      f_(data_.grid_count()),
      c_(data_.grid_count()),
      c_next_(data_.grid_count()),
      matrix_((data_.grid_count() + 1) / 2 * data_.grid_count()),
      calculation_name_(calculation_name) {
    ConstructFunction();
    if (data_.GetIntegrationMethod() == IntegratorType::COLUMN) {
        ConstructMatrixColumn();
    } else {
        std::cout
            << "Other integration methods have not yet been implemented for a solver using matrices"
            << std::endl;
        exit(0);
    }
}
void SimpleMatrixSolver::ConstructFunction() {
    Real x = -data_.r();
    for (size_t i = 0; i < (data_.grid_count() + 1) / 2; ++i) {
        f_[i] = (data_.N() * data_.m(x) - data_.s() * data_.w(x)) /
                (data_.b() + data_.s() * data_.w(x));
        f_[data_.grid_count() - i - 1] = f_[i];
        x += data_.step_size();
    }
}
void SimpleMatrixSolver::ConstructMatrixColumn() {
    ProgressCounter calc_progress("Matrix construction using the column integration method");
    Real x = -data_.r();
    for (size_t i = 0; i < (data_.grid_count() + 1) / 2; ++i) {
        calc_progress.UpdateProgress(1.0 * i / ((data_.grid_count() + 1) / 2));
        Real y = -data_.r();
        for (size_t j = 0; j < data_.grid_count(); ++j) {
            matrix_[i * data_.grid_count() + j] =
                ((j == 0 || j == data_.grid_count() - 1) ? 0.5 : 1) * data_.step_size() *
                data_.b() / (data_.b() + data_.s() * data_.w(x)) * data_.m(x - y);
            y += data_.step_size();
        }
        x += data_.step_size();
    }
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
std::vector<Real> SimpleMatrixSolver::PerformCalculation() {
    ProgressCounter calc_progress(calculation_name_);
    Real x = -data_.r();
    for (size_t i = 0; i < data_.grid_count(); ++i) {
        c_[i] = f_[i] + data_.w(x);
        x += data_.step_size();
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
    return c_;
}
void SimpleMatrixSolver::SaveResults() {
    std::ofstream file(data_.PathToResultFile(), std::ios::out);
    Real x = -data_.r();
    for (size_t i = 0; i < data_.grid_count(); ++i) {
        file << std::fixed << std::setprecision(9) << x << " " << c_[i] << std::endl;
        x += data_.step_size();
    }
}
