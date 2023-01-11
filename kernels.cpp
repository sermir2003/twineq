#include "kernels.h"
#include <cmath>

double Kernels::getN() const {
    return N;
}
Kernels::~Kernels() {
}
RationalKernels::RationalKernels(double A, double p) : A(A), p(p) {
    double p2 = p * p;
    double p4 = p2 * p2;
    N = (A * M_PI * (A + 5 * p2) * (A + 8 * p2)) / (p * (A * A + 21 * A * p2 + 120 * p4));
}
double RationalKernels::m(double x) const {
    return p / (M_PI * (x * x + p * p));
}
double RationalKernels::w(double x) const {
    return A / (x * x + 9 * p * p);  // 9 is (n+1)^2 where n=2
}
ExpKernels::ExpKernels(double A, double B) : A(A), B(B) {
    N = 2.0 / 3 * B + 52.0 / 27 * A;
}
double ExpKernels::m(double x) const {
    return std::exp(-2 * std::abs(x));
}
double ExpKernels::w(double x) const {
    double e_neg_x = std::exp(-std::abs(x));
    double Qx = 1.0 / 3 * A * x * x - 16.0 / 9 * A * std::abs(x) + 56.0 / 27 * A + 1.0 / 3 * B;
    double Rx = A * x * x + B;
    return (e_neg_x * Qx) / (1 + e_neg_x * Rx);
}
