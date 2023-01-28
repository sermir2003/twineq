#include "integrators.h"
#include "real_number.h"

ColumnMethod::ColumnMethod(const Task& data, const std::vector<Real>& c) : Integrator(data, c) {
}
Real ColumnMethod::Integrate(Real x) {
    Real integral = 0;
    Real depends_only_on_x = data_.b() / (data_.b() + data_.s() * data_.w(x));
    Real y = -data_.r();
    for (size_t j = 0; j < data_.grid_count(); ++j) {
        integral += ((j == 0 || j == data_.grid_count() - 1) ? 0.5 : 1) * data_.m(x - y) * c_[j];
        y += data_.step_size();
    }
    integral *= data_.step_size();
    integral *= depends_only_on_x;
    return integral;
}

TrapezoidMethod::TrapezoidMethod(const Task& data, const std::vector<Real>& c)
    : Integrator(data, c) {
}
Real TrapezoidMethod::Integrate(Real x) {
    Real integral = 0;
    Real y = -data_.r();
    for (size_t j = 0; j < data_.grid_count(); ++j) {
        integral += ((j == 0 || j == data_.grid_count() - 1) ? 0.5 : 1) * data_.m(x - y) * c_[j];
        y += data_.step_size();
    }
    integral *= data_.step_size();
    Real depends_only_on_x = data_.b() / (data_.b() + data_.s() * data_.w(x));
    integral *= depends_only_on_x;
    return integral;
}

SimpsonsMethod::SimpsonsMethod(const Task& data, const std::vector<Real>& c)
    : Integrator(data, c) {
}
Real SimpsonsMethod::Integrate(Real x) {
    // TODO: maybe one linear iterating with if is better than three without?
    Real integral = 0;
    Real y = -data_.r();
    for (size_t j = 0; j < data_.grid_count(); ++j) {
        integral += ((j == 0 || j == data_.grid_count() - 1) ? 1
                     : (j % 2 == 1)                          ? 4
                                                             : 2) *
                    data_.m(x - y) * c_[j];
        y += data_.step_size();
    }
    integral *= data_.step_size() / 3;
    Real depends_only_on_x = data_.b() / (data_.b() + data_.s() * data_.w(x));
    integral *= depends_only_on_x;
    return integral;
}
