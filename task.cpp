#include "task.h"

double Task::m(double x) const {
    return kernels_->m(x);
}
double Task::w(double x) const {
    return kernels_->w(x);
}
double Task::b() const {
    return b_;
}
double Task::s() const {
    return s_;
}
double Task::r() const {
    return r_;
}
size_t Task::grid_count() const {
    return grid_count_;
}
double Task::step_size() const {
    return step_size_;
}
size_t Task::iter_count() const {
    return iter_count_;
}
double Task::N() const {
    return N_;
}
const void Task::SaveResults(const std::vector<double>& c) const {
    res_saver_->Save(c);
}
IntegratorType Task::GetIntegrationMethod() const {
    return integration_method_;
}
Task::Task(double b, double s, double r, double N, size_t grid_count, size_t iter_count,
           std::unique_ptr<Kernels> kernels, std::unique_ptr<ResultsSaver> res_saver,
           IntegratorType integration_method, ProblemType problem)
    : b_(b),
      s_(s),
      r_(r),
      N_(N),
      grid_count_(grid_count),
      iter_count_(iter_count),
      kernels_(std::move(kernels)),
      res_saver_(std::move(res_saver)),
      integration_method_(integration_method),
      problem_(problem) {
    step_size_ = 2 * r_ / (grid_count_ - 1);
}
ProblemType Task::GetProblem() const {
    return problem_;
}
Task::Task(const Task& other)
    : b_(other.b_),
      s_(other.s_),
      r_(other.r_),
      N_(other.N_),
      grid_count_(other.grid_count_),
      iter_count_(other.iter_count_),
      kernels_(other.kernels_->Clone()),
      res_saver_(other.res_saver_->Clone()),
      integration_method_(other.integration_method_),
      problem_(other.problem_) {
}
Task& Task::operator=(const Task& other) {
    if (this == &other) {
        return *this;
    }
    *this = Task(other);
    return *this;
}
std::unique_ptr<Kernels> Task::CloneKernels() const {
    return kernels_->Clone();
}
