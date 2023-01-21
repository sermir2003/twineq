#include "task.h"

Task::Task(std::unique_ptr<Kernels> kernels, double b, double s, double r, size_t grid_count,
                 size_t iter_count, std::unique_ptr<ResultsSaver> res_saver,
                 const std::string& integration_method, const std::string& solver_method)
    : kernels_(std::move(kernels)),
      b_(b),
      s_(s),
      r_(r),
      grid_count_(grid_count),
      iter_count_(iter_count),
      res_saver_(std::move(res_saver)),
      integration_method_(integration_method),
      solver_method_(solver_method) {
    step_size_ = 2 * r_ / (grid_count_ - 1);
}
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
    return kernels_->getN();
}
const void Task::SaveResults(const std::vector<double>& c) const {
    res_saver_->Save(c);
}
const std::string& Task::IntegrationMethod() const {
    return integration_method_;
}
const std::string& Task::SolverMethod() const {
    return solver_method_;
}
