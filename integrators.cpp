#include "integrators.h"

ColumnMethod::ColumnMethod(const Task& data, const std::vector<double>& c) : Integrator(data, c) {
}
double ColumnMethod::Integrate(double x) {
    double integral = 0;
    double depends_only_on_x = data_.b() / (data_.b() + data_.s() * data_.w(x));
    double y = -data_.r();
    for (size_t j = 0; j < data_.grid_count(); ++j) {
        integral += ((j == 0 || j == data_.iter_count() - 1) ? 0.5 : 1) * data_.m(x - y) * c_[j];
        y += data_.step_size();
    }
    integral *= data_.step_size();
    integral *= depends_only_on_x;
    return integral;
}

TrapezoidMethod::TrapezoidMethod(const Task& data, const std::vector<double>& c)
    : Integrator(data, c) {
}
double TrapezoidMethod::Integrate(double x) {
    double integral = 0;
    double y = -data_.r();
    for (size_t j = 0; j < data_.grid_count(); ++j) {
        integral += ((j == 0 || j == data_.iter_count() - 1) ? 0.5 : 1) * data_.m(x - y) * c_[j];
        y += data_.step_size();
    }
    integral *= data_.step_size();
    double depends_only_on_x = data_.b() / (data_.b() + data_.s() * data_.w(x));
    integral *= depends_only_on_x;
    return integral;
}

SimpsonsMethod::SimpsonsMethod(const Task& data, const std::vector<double>& c)
    : Integrator(data, c) {
}
double SimpsonsMethod::Integrate(double x) {
    // TODO: maybe one linear iterating with if is better than three without?
    double integral = 0;
    double y = -data_.r();
    for (size_t j = 0; j < data_.grid_count(); ++j) {
        integral += ((j == 0 || j == data_.grid_count() - 1) ? 1
                     : (j % 2 == 1)                          ? 4
                                                             : 2) *
                    data_.m(x - y) * c_[j];
        y += data_.step_size();
    }
    integral *= data_.step_size() / 3;
    double depends_only_on_x = data_.b() / (data_.b() + data_.s() * data_.w(x));
    integral *= depends_only_on_x;
    return integral;
}
