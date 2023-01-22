#pragma once
#include <memory>

enum class KernelsType {
    DANCHENKO_RATIONAL,
    DANCHENKO_EXP_KERNEL,
};

/**
 * Abstract class for birth and death kernels
 */
class Kernels {
public:
    virtual double m(double x) const = 0;
    virtual double w(double x) const = 0;
    virtual double getN() const = 0;
    virtual ~Kernels();
    virtual std::unique_ptr<Kernels> Clone() const = 0;
};

/**
 * Class for rational Danchenko kernels
 */
class DanchenkoRationalKernels : public Kernels {
private:
    double A;
    double p;

public:
    DanchenkoRationalKernels(double A, double p);
    double m(double x) const override;
    double w(double x) const override;
    double getN() const override;
    std::unique_ptr<Kernels> Clone() const override;
};

/**
 * Class for exponential Danchenko kernels
 */
class DanchenkoExpKernels : public Kernels {
private:
    double A;
    double B;

public:
    DanchenkoExpKernels(double A, double B);
    double m(double x) const override;
    double w(double x) const override;
    double getN() const override;
    std::unique_ptr<Kernels> Clone() const override;
};
