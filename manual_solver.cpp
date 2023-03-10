#include "manual_solver.h"
#include <fstream>
#include <iostream>
#include <iomanip>

ManualSolver::ManualSolver(const Task& task, const std::string& calculation_name)
    : data_(std::move(task)),
      f_(data_.grid_count()),
      c_(data_.grid_count()),
      c_next_(data_.grid_count()),
      calculation_name_(calculation_name) {
    std::cout << "Initialization of " << calculation_name << "..." << std::endl;
    if (data_.GetIntegrationMethod() == IntegratorType::COLUMN) {
        integrator_ = std::make_unique<ColumnMethod>(data_, c_);
    } else if (data_.GetIntegrationMethod() == IntegratorType::TRAPEZOID) {
        integrator_ = std::make_unique<TrapezoidMethod>(data_, c_);
    } else if (data_.GetIntegrationMethod() == IntegratorType::SIMPSONS) {
        integrator_ = std::make_unique<SimpsonsMethod>(data_, c_);
    }
    ConstructFunction();
    std::cout << "Initialization of " << calculation_name << " --- Done!" << std::endl;
}
void ManualSolver::ConstructFunction() {
    std::cout << "Construct function..." << std::endl;
    Real x = -data_.r();
    for (size_t i = 0; i < (data_.grid_count() + 1) / 2; ++i) {
        f_[i] = (data_.N() * data_.m(x) - data_.s() * data_.w(x)) /
                (data_.b() + data_.s() * data_.w(x));
        f_[data_.grid_count() - i - 1] = f_[i];
        x += data_.step_size();
    }
    std::cout << "Construct function --- Done!" << std::endl;
}
std::vector<Real> ManualSolver::PerformCalculation() {
    ProgressCounter calc_progress(calculation_name_);
    for (size_t i = 0; i < data_.grid_count(); ++i) {
        c_[i] = f_[i];
    }
    for (size_t iteration = 1; iteration < data_.iter_count(); ++iteration) {
        Real x = -data_.r();
        for (size_t i = 0; i < (data_.grid_count() + 1) / 2; ++i) {
            Real integral = integrator_->Integrate(x);
            c_next_[i] = f_[i] + integral;
            c_next_[data_.grid_count() - i - 1] = c_next_[i];
            x += data_.step_size();
        }
        std::swap(c_, c_next_);
        calc_progress.UpdateProgress(1.0 * iteration / data_.iter_count());
    }
    calc_progress.FinishAction();
    if (data_.GetSaveToFile()) {
        SaveResults();
    }
    return c_;
}
void ManualSolver::SaveResults() {
    std::ofstream file(data_.PathToResultFile(), std::ios::out);
    Real x = -data_.r();
    for (size_t i = 0; i < data_.grid_count(); ++i) {
        file << std::fixed << std::setprecision(9) << x << " " << c_[i] << std::endl;
        x += data_.step_size();
    }
}
