#pragma once
#include "kernels.h"
#include "results_saver.h"
#include "integrator_types.h"
#include <cstdint>
#include <string>
#include <memory>
#include <vector>

enum class ProblemType {
    TWIN_EQUATION,
    ORIGINAL_EQUATION,
};

/**
 * Class for holding biological and technical parameters of the current task
 */
class Task {
private:
    double b_;           /// intrinsic rates of birth
    double s_;           /// the same as d'
    double r_;           /// segment size: [-r; r]
    double N_;           /// Control parameter
    size_t grid_count_;  /// the number of grid nodes for which calculations are performed
    double step_size_;   /// the scale of the grid of nodes for which calculations are performed
    size_t iter_count_;  /// number of iterations
    std::unique_ptr<Kernels> kernels_;         /// birth and death kernels
    std::unique_ptr<ResultsSaver> res_saver_;  /// class for saving c_
    IntegratorType integration_method_;        /// the method that should be used for integration
    ProblemType problem_;

public:
    Task() = delete;
    Task(double b, double s, double r, double N, size_t grid_count, size_t iter_count,
         std::unique_ptr<Kernels> kernels, std::unique_ptr<ResultsSaver> res_saver,
         IntegratorType integration_method, ProblemType problem);

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
    IntegratorType GetIntegrationMethod() const;
    ProblemType GetProblem() const;
};
