#include "manual_solver.h"
#include <iostream>
#include <iomanip>

ManualSolver::ManualSolver(Task&& task)
    : data_(std::move(task)),
      f_(data_.grid_count()),
      c_(data_.grid_count()),
      c_next_(data_.grid_count()) {
    if (data_.IntegrationMethod() == IntegratorType::COLUMN) {
        integrator_ = std::make_unique<ColumnMethod>(data_, c_);
    } else if (data_.IntegrationMethod() == IntegratorType::TRAPEZOID) {
        integrator_ = std::make_unique<TrapezoidMethod>(data_, c_);
    } else if (data_.IntegrationMethod() == IntegratorType::SIMPSONS) {
        integrator_ = std::make_unique<SimpsonsMethod>(data_, c_);
    }
    ConstructFunction();
    PerformCalculation();
}
void ManualSolver::ConstructFunction() {
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
void ManualSolver::PerformCalculation() {
    ProgressCounter calc_progress("Calculation");
    for (size_t i = 0; i < data_.grid_count(); ++i) {
        c_[i] = f_[i];
    }
    for (size_t iteration = 1; iteration < data_.iter_count(); ++iteration) {
        double x = -data_.r();
        for (size_t i = 0; i < (data_.grid_count() + 1) / 2; ++i) {
            double integral = integrator_->Integrate(x);
            c_next_[i] = f_[i] + integral;
            c_next_[data_.grid_count() - i - 1] = c_next_[i];
            x += data_.step_size();
        }
        std::swap(c_, c_next_);
        calc_progress.UpdateProgress(1.0 * iteration / data_.iter_count());
    }
    calc_progress.FinishAction();
    data_.SaveResults(c_);
}
