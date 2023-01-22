#include "kernels.h"
#include <cmath>

Kernels::~Kernels() {
}
DanchenkoRationalKernels::DanchenkoRationalKernels(double A, double p) : A(A), p(p) {
}
double DanchenkoRationalKernels::m(double x) const {
    return p / (M_PI * (x * x + p * p));
}
double DanchenkoRationalKernels::w(double x) const {
    return A / (x * x + 9 * p * p);  // 9 is (n+1)^2 where n=2
}
double DanchenkoRationalKernels::getN() const {
    double p2 = p * p;
    double N = (A * M_PI * (A + 5 * p2) * (A + 8 * p2)) / (p * (A * A + 21 * A * p2 + 120 * p2));
    return N;
}
DanchenkoExpKernels::DanchenkoExpKernels(double A, double B) : A(A), B(B) {
}
double DanchenkoExpKernels::m(double x) const {
    return std::exp(-2 * std::abs(x));
}
double DanchenkoExpKernels::w(double x) const {
    double e_neg_x = std::exp(-std::abs(x));
    double Qx = 1.0 / 3 * A * x * x - 16.0 / 9 * A * std::abs(x) + 56.0 / 27 * A + 1.0 / 3 * B;
    double Rx = A * x * x + B;
    return (e_neg_x * Qx) / (1 + e_neg_x * Rx);
}
double DanchenkoExpKernels::getN() const {
    double N = 2.0 / 3 * B + 52.0 / 27 * A;
    return N;
}
