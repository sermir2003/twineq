#include "scalar_product_L2.h"

ScalarProductL2::ScalarProductL2(const Task& task, const std::vector<double>& c) : data_(task), c_(c) {
}
double ScalarProductL2::Calculate() const {
    double integral = 0;
    double x = -data_.r();
    for (size_t i = 0; i < data_.grid_count(); ++i) {
        integral += data_.w(x) * (c_[i] + 1);
        x += data_.step_size();
    }
    integral *= data_.s();
    return integral;
}
