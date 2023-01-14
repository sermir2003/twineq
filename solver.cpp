#include "solver.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <chrono>

typedef std::chrono::time_point<std::chrono::high_resolution_clock> Time;

Solver::Solver(Task&& problem)
    : data_(std::move(problem)),
      f_(data_.grid_count()),
      c_(data_.grid_count()),
      c_next_(data_.grid_count()) {
    if (data_.IntegrationMethod() == "Column") {
        integrator_ = std::make_unique<ColumnMethod>(data_, c_);
    } else if (data_.IntegrationMethod() == "Trapezoid") {
        integrator_ = std::make_unique<TrapezoidMethod>(data_, c_);
    } else if (data_.IntegrationMethod() == "Simpsons") {
        integrator_ = std::make_unique<SimpsonsMethod>(data_, c_);
    }
    ConstructFunction();
    PerformCalculation();
}
void Solver::ConstructFunction() {
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
void Solver::PerformCalculation() {
    InitProgress();
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
        UpdateProgress(1.0 * iteration / data_.iter_count());
    }
    CompleteProgress();
    SaveResults();
}
void Solver::SaveResults() {
    std::ofstream file(data_.PathToResFile(), std::ios::out);
    double x = -data_.r();
    for (size_t i = 0; i < data_.grid_count(); ++i) {
        file << std::fixed << std::setprecision(9) << x << " " << c_[i] << std::endl;
        x += data_.step_size();
    }
}
void Solver::InitProgress() {
    std::cout << "Calculation started" << std::endl;
    std::cout << "Progress: 0%" << std::flush;
    start_time_ = std::chrono::high_resolution_clock::now();
}
void Solver::UpdateProgress(double progress) {
    static const std::string kBleachingLine = "\r" + std::string(100, ' ') + '\r';
    std::cout << kBleachingLine;
    Time cur_time = std::chrono::high_resolution_clock::now();
    auto delta =
        std::chrono::duration_cast<std::chrono::milliseconds>(cur_time - start_time_).count();
    auto time_left = 1.0 * delta / progress * (1 - progress);
    std::cout << "Progress: " << std::fixed << std::setprecision(1) << 100 * progress << "%"
              << "; time left: " << std::setprecision(0) << time_left / 1000 << " s"
              << "; time has passed: " << delta / 1000 << " s" << std::flush;
}
void Solver::CompleteProgress() {
    static const std::string kBleachingLine = "\r" + std::string(100, ' ') + '\r';
    Time cur_time = std::chrono::high_resolution_clock::now();
    auto delta =
        std::chrono::duration_cast<std::chrono::milliseconds>(cur_time - start_time_).count();
    std::cout << kBleachingLine << "Progress: 100%"
              << "; time has passed: " << std::setprecision(0) << delta / 1000 << " s" << std::endl;
    std::cout << "Calculation finished" << std::endl;
}
