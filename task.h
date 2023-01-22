#pragma once
#include "kernels.h"
#include "results_saver.h"
#include <cstdint>
#include <string>
#include <memory>
#include <vector>

/**
 * Class for holding biological and technical parameters of the current problem
 */
class Task {
private:
    std::unique_ptr<Kernels> kernels_;  /// birth and death kernels
                                        //    const double d_ = 0;  /// intrinsic rates of death
    double b_;                          /// intrinsic rates of birth
    double s_;                          /// the same as d'
    double r_;                          /// segment size: [-r; r]
    double N_;                          /// Control parameter
    size_t grid_count_;  /// the number of grid nodes for which calculations are performed
    double step_size_;   /// the scale of the grid of nodes for which calculations are performed
    size_t iter_count_;  /// number of iterations
    std::unique_ptr<ResultsSaver> res_saver_;  /// class for saving c_
    std::string integration_method_;   /// the method that should be used for integration
    std::string solver_method_;   /// the solver
public:
    Task() = delete;
    Task(std::unique_ptr<Kernels> kernels, double b, double s, double r, double N, size_t grid_count,
            size_t iter_count, std::unique_ptr<ResultsSaver> res_saver,
            const std::string& integration_method, const std::string& solver_method);

    double m(double x) const;
    double w(double x) const;
    double N() const;
    double b() const;
    double s() const;
    double r() const;
    size_t grid_count() const;
    double step_size() const;
    size_t iter_count() const;
    const void SaveResults(const std::vector<double>& c) const;
    const std::string& IntegrationMethod() const;
    const std::string& SolverMethod() const;
};
