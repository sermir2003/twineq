#pragma once
#include "kernels.h"
#include "integrator_types.h"
#include <cstdint>
#include <string>
#include <memory>
#include <vector>
#include "real_number.h"

enum class ProblemType {
    TWIN_EQUATION,
    ORIGINAL_EQUATION,
};

enum class IterationType {
    MANUAL,
    MATRIX,
};

/**
 * Class for holding biological and technical parameters of the current task
 */
class Task {
private:
    Real b_;           /// intrinsic rates of birth
    Real s_;           /// the same as d'
    Real r_;           /// segment size: [-r; r]
    Real N_;           /// Control parameter
    size_t grid_count_;  /// the number of grid nodes for which calculations are performed
    Real step_size_;   /// the scale of the grid of nodes for which calculations are performed
    size_t iter_count_;  /// number of iterations
    std::unique_ptr<Kernels> kernels_;  /// birth and death kernels
    bool save_c_to_file_;
    std::string path_to_result_file_;
    IntegratorType integration_method_;  /// the method that should be used for integration
    IterationType iteration_method_;     /// the method that should be used for integration
    ProblemType problem_;

public:
    friend void SolutionLauncher(Task&& task);
    friend class TaskFileIO;

    Task() = default;
    Task(const Task& other) = delete;
    Task(Task&& other) = default;
    Task& operator=(const Task& other) = delete;
    Task& operator=(Task&& other) = default;

    Real m(Real x) const;
    Real w(Real x) const;
    Real N() const;
    Real b() const;
    Real s() const;
    Real r() const;
    size_t grid_count() const;
    Real step_size() const;
    size_t iter_count() const;
    IntegratorType GetIntegrationMethod() const;
    IterationType GetIterationMethod() const;
    ProblemType GetProblem() const;
    std::unique_ptr<Kernels> CloneKernels() const;
    bool GetSaveToFile() const;
    std::string PathToResultFile() const;
};
