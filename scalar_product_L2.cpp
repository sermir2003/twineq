#include "scalar_product_L2.h"

#include <iostream>
#include <iomanip>

ScalarProductL2::ScalarProductL2(const Task& task, const std::vector<double>& c) : data_(task), c_(c) {
}
double ScalarProductL2::Calculate() const {
    double integral = 0;
    double x = -data_.r();
    for (size_t i = 0; i < data_.grid_count(); ++i) {
        integral += ((i == 0 || i == data_.grid_count() - 1) ? 0.5 : 1) * data_.w(x) * (c_[i] + 1);
        x += data_.step_size();
    }
    std::cout << "debug: " << std::fixed << std::setprecision(9) << data_.step_size() << std::endl;
    integral *= data_.step_size();
    integral *= data_.s();
    return integral;
}
