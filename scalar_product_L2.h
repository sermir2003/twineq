#pragma once
#include "task.h"

class ScalarProductL2 {
private:
    const Task& data_;
    const std::vector<double>& c_;

public:
    ScalarProductL2(const Task& task, const std::vector<double>& c);
    double Calculate() const;
};
