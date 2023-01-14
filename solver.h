#pragma once
#include <vector>
#include "task.h"
#include <chrono>

class Solver;

class Integrator {
protected:
    const Solver& solver_;
public:
    Integrator(Solver& solver) : solver_(solver) {
    }
    virtual double Integrate(double x) = 0;
    virtual ~Integrator() {
    }
};

class ColumnMethod : public Integrator {
public:
    ColumnMethod(Solver& solver);
    double Integrate(double x) override;
};

class TrapezoidMethod : public Integrator {
public:
    TrapezoidMethod(Solver& solver);
    double Integrate(double x) override;
};

class SimpsonsMethod : public Integrator {
public:
    SimpsonsMethod(Solver& solver);
    double Integrate(double x) override;
};

class Solver {
private:
    Task data_;
    std::vector<double> f_;
    std::vector<double> c_;
    std::vector<double> c_next_;
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time_;
    std::unique_ptr<Integrator> integrator_;
private:
    void PerformCalculation();  // Probably should be turned off from the constructor
    void ConstructFunction();
    void SaveResults();
    void InitProgress();
    void UpdateProgress(double progress);
    void CompleteProgress();
public:
    friend Integrator;
    friend ColumnMethod;
    friend TrapezoidMethod;
    friend SimpsonsMethod;
    Solver(Task&& problem);
};
