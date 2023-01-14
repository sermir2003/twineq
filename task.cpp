#include "task.h"

Task::Task(std::unique_ptr<Kernels> kernels, double b, double s, double r, size_t grid_count,
                 size_t iter_count, const std::string& path_to_result_file,
                 const std::string& integration_method)
    : kernels_(std::move(kernels)),
      b_(b),
      s_(s),
      r_(r),
      grid_count_(grid_count),
      iter_count_(iter_count),
      path_to_result_file_(path_to_result_file),
      integration_method_(integration_method) {
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
const std::string& Task::PathToResFile() const {
    return path_to_result_file_;
}
const std::string& Task::IntegrationMethod() const {
    return integration_method_;
}
