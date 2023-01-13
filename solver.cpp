#include "solver.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <chrono>

typedef std::chrono::time_point<std::chrono::high_resolution_clock> Time;

Solver::Solver(Problem&& problem)
    : data_(std::move(problem)),
      f_(data_.grid_count()),
      c_(data_.grid_count()),
      c_next_(data_.grid_count()) {
    ConstructFunction();
    PerformCalculation();
}
void Solver::ConstructFunction() {
    std::cout << "Construct function..." << std::endl;
    double x = -data_.r();
    for (size_t i = 0; i < data_.grid_count(); ++i) {
        f_[i] = (data_.N() * data_.m(x) - data_.s() * data_.w(x)) /
                (data_.b() + data_.s() * data_.w(x));
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
        for (size_t i = 0; i < data_.grid_count(); ++i) {
            double integral = 0;
            double depends_only_on_x = data_.b() / (data_.b() + data_.s() * data_.w(x));
            double y = -data_.r();
            for (size_t j = 0; j < data_.grid_count(); ++j) {
                integral +=
                    ((iteration == 0 || iteration == data_.iter_count() - 1) ? data_.step_size() / 2
                                                                             : data_.step_size()) *
                    data_.m(x - y) * c_[j];
                y += data_.step_size();
            }
            integral *= depends_only_on_x;
            c_next_[i] = f_[i] + integral;
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
}
