#pragma once
#include "service_parameters_types.h"
#include "task.h"
#include <vector>
#include "real_number.h"

class Integrator {
protected:
    const Task& data_;
    const std::vector<Real>& c_;

public:
    Integrator(const Task& data, const std::vector<Real>& c) : data_(data), c_(c) {
    }
    virtual Real Integrate(Real x) = 0;
    virtual ~Integrator() {
    }
};

class ColumnMethod : public Integrator {
public:
    ColumnMethod(const Task& data, const std::vector<Real>& c);
    Real Integrate(Real x) override;
};

class TrapezoidMethod : public Integrator {
public:
    TrapezoidMethod(const Task& data, const std::vector<Real>& c);
    Real Integrate(Real x) override;
};

class SimpsonsMethod : public Integrator {
public:
    SimpsonsMethod(const Task& data, const std::vector<Real>& c);
    Real Integrate(Real x) override;
};
