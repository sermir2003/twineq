#pragma once
#include "kernels.h"
#include <cstdint>
#include <string>
#include <memory>
#include <vector>
#include "real_number.h"
#include "service_parameters_types.h"

/**
 * Class for holding biological and technical parameters of the current task
 */
class Task {
private:
    Real b_;             /// intrinsic rates of birth
    Real s_;             /// the same as d'
    Real r_;             /// segment size: [-r; r]
    Real N_;             /// Control parameter
    size_t grid_count_;  /// the number of grid nodes for which calculations are performed
    Real step_size_;     /// the scale of the grid of nodes for which calculations are performed
    size_t iter_count_;  /// number of iterations
    std::unique_ptr<Kernels> kernels_;  /// birth and death kernels
    bool save_c_to_file_;
    std::string path_to_result_file_;
    IntegratorType integration_method_;  /// the method that should be used for integration
    IterationType iteration_method_;     /// the method that should be used for integration
    ProblemType problem_;

public:
    friend void SolutionLauncher(Task&& task);

    Task() = default;
    Task(const Task& other) = delete;
    Task(Task&& other) = default;
    Task& operator=(const Task& other) = delete;
    Task& operator=(Task&& other) = default;

    static void CreateTaskFile(std::string path_task_file);
    Task(std::string task_file_name);

    Real m(Real x) const {
        return kernels_->m(x);
    };
    Real w(Real x) const {
        return kernels_->w(x);
    };
    Real N() const {
        return N_;
    };
    Real b() const {
        return b_;
    };
    Real s() const {
        return s_;
    };
    Real r() const {
        return r_;
    };
    size_t grid_count() const {
        return grid_count_;
    };
    Real step_size() const {
        return step_size_;
    };
    size_t iter_count() const {
        return iter_count_;
    };
    IntegratorType GetIntegrationMethod() const {
        return integration_method_;
    }
    IterationType GetIterationMethod() const {
        return iteration_method_;
    }
    ProblemType GetProblem() const {
        return problem_;
    }
    bool GetSaveToFile() const {
        return save_c_to_file_;
    }
    std::string PathToResultFile() const {
        return path_to_result_file_;
    }
};
