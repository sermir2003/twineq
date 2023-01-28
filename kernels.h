#pragma once
#include <memory>
#include "real_number.h"

enum class KernelsType {
    DANCHENKO_RATIONAL,
    DANCHENKO_EXP_KERNEL,
};

/**
 * Abstract class for birth and death kernels
 */
class Kernels {
public:
    virtual Real m(Real x) const = 0;
    virtual Real w(Real x) const = 0;
    virtual Real getN() const = 0;
    virtual ~Kernels();
    virtual std::unique_ptr<Kernels> Clone() const = 0;
};

/**
 * Class for rational Danchenko kernels
 */
class DanchenkoRationalKernels : public Kernels {
private:
    Real A;
    Real p;

public:
    DanchenkoRationalKernels(Real A, Real p);
    Real m(Real x) const override;
    Real w(Real x) const override;
    Real getN() const override;
    std::unique_ptr<Kernels> Clone() const override;
};

/**
 * Class for exponential Danchenko kernels
 */
class DanchenkoExpKernels : public Kernels {
private:
    Real A;
    Real B;

public:
    DanchenkoExpKernels(Real A, Real B);
    Real m(Real x) const override;
    Real w(Real x) const override;
    Real getN() const override;
    std::unique_ptr<Kernels> Clone() const override;
};
