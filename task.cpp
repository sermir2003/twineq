#include "task.h"

Real Task::m(Real x) const {
    return kernels_->m(x);
}
Real Task::w(Real x) const {
    return kernels_->w(x);
}
Real Task::b() const {
    return b_;
}
Real Task::s() const {
    return s_;
}
Real Task::r() const {
    return r_;
}
size_t Task::grid_count() const {
    return grid_count_;
}
Real Task::step_size() const {
    return step_size_;
}
size_t Task::iter_count() const {
    return iter_count_;
}
Real Task::N() const {
    return N_;
}
IntegratorType Task::GetIntegrationMethod() const {
    return integration_method_;
}
ProblemType Task::GetProblem() const {
    return problem_;
}
std::unique_ptr<Kernels> Task::CloneKernels() const {
    return kernels_->Clone();
}
bool Task::GetSaveToFile() const {
    return save_c_to_file_;
}
std::string Task::PathToResultFile() const {
    return path_to_result_file_;
}
IterationType Task::GetIterationMethod() const {
    return iteration_method_;
}
