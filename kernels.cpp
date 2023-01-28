#include "kernels.h"
#include <cmath>
#include "real_number.h"

Kernels::~Kernels() {
}
DanchenkoRationalKernels::DanchenkoRationalKernels(Real A, Real p) : A(A), p(p) {
}
Real DanchenkoRationalKernels::m(Real x) const {
    return p / (M_PI * (x * x + p * p));
}
Real DanchenkoRationalKernels::w(Real x) const {
    return A / (x * x + 9 * p * p);  // 9 is (n+1)^2 where n=2
}
Real DanchenkoRationalKernels::getN() const {
    Real p2 = p * p;
    Real N = (A * M_PI * (A + 5 * p2) * (A + 8 * p2)) / (p * (A * A + 21 * A * p2 + 120 * p2));
    return N;
}
std::unique_ptr<Kernels> DanchenkoRationalKernels::Clone() const {
    return std::make_unique<DanchenkoRationalKernels>(A, p);
}
DanchenkoExpKernels::DanchenkoExpKernels(Real A, Real B) : A(A), B(B) {
}
Real DanchenkoExpKernels::m(Real x) const {
    return std::exp(-2 * std::abs(x));
}
Real DanchenkoExpKernels::w(Real x) const {
    Real e_neg_x = std::exp(-std::abs(x));
    Real Qx = 1.0 / 3 * A * x * x - 16.0 / 9 * A * std::abs(x) + 56.0 / 27 * A + 1.0 / 3 * B;
    Real Rx = A * x * x + B;
    return (e_neg_x * Qx) / (1 + e_neg_x * Rx);
}
Real DanchenkoExpKernels::getN() const {
    Real N = 2.0 / 3 * B + 52.0 / 27 * A;
    return N;
}
std::unique_ptr<Kernels> DanchenkoExpKernels::Clone() const {
    return std::make_unique<DanchenkoExpKernels>(A, B);
}
