#pragma once
#include "kernels.h"
#include <cstdint>
#include <string>
#include <memory>
#include <string>

/**
 * Class for holding biological and technical parameters of the current problem
 */
class Problem {
private:
    std::unique_ptr<Kernels> kernels_;  /// birth and death kernels
//    const double d_ = 0;  /// intrinsic rates of death
    double b_;  /// intrinsic rates of birth
    double s_;  /// the same as d'
    double r_;  /// segment size: [-r; r] TODO: find out what the hell it is
    size_t grid_count_;  /// the number of grid nodes for which calculations are performed
    double step_size_;  /// the scale of the grid of nodes for which calculations are performed
    size_t iter_count_;  /// number of iterations
    std::string path_to_result_file_;  /// just path to result file
public:
    Problem() = delete;
    Problem(std::unique_ptr<Kernels> kernels, double b, double s, double r, size_t grid_count,
            size_t iter_count, const std::string& path_to_result_file);

    double m(double x) const;
    double w(double x) const;
    double N() const;
    double b() const;
    double s() const;
    double r() const;
    size_t grid_count() const;
    double step_size() const;
    size_t iter_count() const;
    std::string PathToResFile() const;
};