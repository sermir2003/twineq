#pragma once

/**
 * Abstract class for birth and death kernels
 */
class Kernels {
protected:
    double N;  /// twin equation Control parameter
public:
    virtual double m(double x) const = 0;
    virtual double w(double x) const = 0;
    virtual double getN() const;
    virtual ~Kernels();
};

/**
 * Class for rational Danchenko kernels
 */
class RationalKernels : public Kernels {
private:
    double A;
    double p;
public:
    RationalKernels(double A, double p);
    double m(double x) const override;
    double w(double x) const override;
};

/**
 * Class for exponential Danchenko kernels
 */
class ExpKernels : public Kernels {
private:
    double A;
    double B;
public:
    ExpKernels(double A, double B);
    double m(double x) const override;
    double w(double x) const override;
};
