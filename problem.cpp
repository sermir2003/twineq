#include "problem.h"

Problem::Problem(std::unique_ptr<Kernels> kernels, double b, double s, double r, size_t grid_count,
                 size_t iter_count, const std::string& path_to_result_file) :
      kernels_(std::move(kernels)), b_(b), s_(s), r_(r), grid_count_(grid_count),
      iter_count_(iter_count), path_to_result_file_(path_to_result_file) {
    step_size_ = 2 * r_ / (grid_count_ - 1);
}
double Problem::m(double x) const {
    return kernels_->m(x);
}
double Problem::w(double x) const {
    return kernels_->w(x);
}
double Problem::b() const {
    return b_;
}
double Problem::s() const {
    return s_;
}
double Problem::r() const {
    return r_;
}
size_t Problem::grid_count() const {
    return grid_count_;
}
double Problem::step_size() const {
    return step_size_;
}
size_t Problem::iter_count() const {
    return iter_count_;
}
double Problem::N() const {
    return kernels_->getN();
}
std::string Problem::PathToResFile() const {
    return path_to_result_file_;
}
