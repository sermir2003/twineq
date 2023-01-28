#pragma once
#include "task.h"

class ScalarProductL2 {
private:
    const Task& data_;
    const std::vector<Real>& c_;

public:
    ScalarProductL2(const Task& task, const std::vector<Real>& c);
    Real Calculate() const;
};
