#pragma once
#include "task.h"
#include <vector>

class Integrator {
protected:
    const Task& data_;
    const std::vector<double>& c_;

public:
    Integrator(const Task& data, const std::vector<double>& c) : data_(data), c_(c) {
    }
    virtual double Integrate(double x) = 0;
    virtual ~Integrator() {
    }
};

class ColumnMethod : public Integrator {
public:
    ColumnMethod(const Task& data, const std::vector<double>& c);
    double Integrate(double x) override;
};

class TrapezoidMethod : public Integrator {
public:
    TrapezoidMethod(const Task& data, const std::vector<double>& c);
    double Integrate(double x) override;
};

class SimpsonsMethod : public Integrator {
public:
    SimpsonsMethod(const Task& data, const std::vector<double>& c);
    double Integrate(double x) override;
};
