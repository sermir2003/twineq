#include "solver.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <chrono>

typedef std::chrono::time_point<std::chrono::high_resolution_clock> Time;

Solver::Solver(Problem&& problem) : data_(std::move(problem)), f_(data_.grid_count()),
       c_(data_.grid_count()), c_next_(data_.grid_count()) {
    std::cout << "Construct Solver instance..." << std::endl;
    ConstructFunction();
    PerformCalculation();
    std::cout << "Construct Solver instance --- Done!" << std::endl;
}
void Solver::ConstructFunction() {
    std::cout << "Construct function..." << std::endl;
    double x = -data_.r();
    for (size_t i = 0; i < data_.grid_count(); ++i) {
        f_[i] = (data_.N() * data_.m(x) - data_.s() * data_.w(x)) / (data_.b() + data_.s() * data_.w(x));
        x += data_.step_size();
    }
    std::cout << "Construct function --- Done!" << std::endl;
}
void Solver::PerformCalculation() {
    InitProgress();
    time_start_ = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < data_.grid_count(); ++i) {
        c_[i] = f_[i];
    }
    for (size_t iteration = 1; iteration < data_.iter_count(); ++iteration) {
        double x = -data_.r();
        for (size_t i = 0; i < data_.grid_count(); ++i) {
            double integral = 0;
            double ratio_before_int = data_.b() / (data_.b() + data_.s() * data_.w(x));
            double y = -data_.r();
            for (size_t j = 0; j < data_.grid_count(); ++j) {
                integral += ((iteration == 0 || iteration == data_.iter_count() - 1)
                                 ? data_.step_size() / 2 : data_.step_size())
                            * data_.m(x - y) * c_[j];
                y += data_.step_size();
            }
            integral *= ratio_before_int;
            c_next_[i] = f_[i] + integral;
            x += data_.step_size();
        }
        std::swap(c_, c_next_);
        UpdateProgress(100.0 * iteration / data_.iter_count());
    }
    CompleteProgress();
    SaveResults();
}
void Solver::SaveResults() {
    std::ofstream file(data_.PathToResFile(), std::ios::out);
    double x = -data_.r();
    for (size_t i = 0; i < data_.grid_count(); ++i) {
        if (x >= 0 - data_.step_size() / 2) {
            file << std::fixed << std::setprecision(9) << x << " " << c_[i] << std::endl;
        }
        x += data_.step_size();
    }
}
void Solver::InitProgress() {
    std::cout << "Calculation started" << std::endl;
    std::cout << "Progress: 0%" << std::flush;
}
void Solver::UpdateProgress(double progress) {
    static const std::string kBleachingLine = "\r" + std::string(70, ' ');
    std::cout << kBleachingLine;
    Time cur_time = std::chrono::high_resolution_clock::now();
    auto d = cur_time - time_start_;
    std::cout << "\rProgress: " << std::fixed << std::setprecision(1) << progress << "%" <<
        "; Time has passed: " << std::chrono::duration_cast<std::chrono::milliseconds>(d).count() << " ms" <<
        std::flush;
}
void Solver::CompleteProgress() {
    Time cur_time = std::chrono::high_resolution_clock::now();
    auto d = cur_time - time_start_;
    static const std::string kBleachingLine = "\r" + std::string(70, ' ');
    std::cout << kBleachingLine << "\rProgress: 100%" <<
        "; Time has passed: " << std::chrono::duration_cast<std::chrono::milliseconds>(d).count() << " ms" <<
        std::endl;
}
