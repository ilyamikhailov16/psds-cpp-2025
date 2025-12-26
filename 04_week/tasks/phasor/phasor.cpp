#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <iomanip>


struct ExpTag{};
struct DegTag{};
struct AlgTag{};


class Phasor
{
    double real;
    double imag;

public:
    Phasor() : real(0.0), imag(0.0) {}
    Phasor(double amplitude, double phase) : real(amplitude * std::cos(phase)), imag(amplitude * std::sin(phase)) {}
    Phasor(double amplitude, double phase, ExpTag) : Phasor(amplitude, phase) {}
    Phasor(double amplitude, double phase, DegTag) : Phasor(amplitude, M_PI * phase / 180) {}
    Phasor(double real, double imag, AlgTag) : real(real), imag(imag) {}

    void SetPolar(const double &r, const double &angle);
    void SetCartesian(const double &x, const double &y);
    double Magnitude() const;
    double Abs() const;
    double Phase() const;
    double Angle() const;
    double PhaseDeg() const;
    double AngleDeg() const;
    double Real() const;
    double Imag() const;
    Phasor Conj() const;
    Phasor Inv() const;

    Phasor operator+(const Phasor &other) const;
    Phasor operator-(const Phasor &other) const;
    Phasor operator*(const Phasor &other) const;
    Phasor operator/(const Phasor &other) const;
    Phasor operator-() const;

    Phasor& operator+=(const Phasor &other);
    Phasor& operator-=(const Phasor &other);
    Phasor& operator*=(const Phasor &other);
    Phasor& operator/=(const Phasor &other);

    bool operator==(const Phasor &other) const;
    bool operator!=(const Phasor &other) const;

    friend std::ostream& operator<<(std::ostream& os, const Phasor& phasor);
};


Phasor operator+(const Phasor &p, double scalar);
Phasor operator+(double scalar, const Phasor &p);
Phasor operator-(const Phasor &p, double scalar);
Phasor operator-(double scalar, const Phasor &p);
Phasor operator*(const Phasor &p, double scalar);
Phasor operator*(double scalar, const Phasor &p);
Phasor operator/(const Phasor &p, double scalar);
Phasor operator/(double scalar, const Phasor &p);

void Phasor::SetPolar(const double &r, const double &angle)
{
    real = r * std::cos(angle);
    imag = r * std::sin(angle);
}

void Phasor::SetCartesian(const double &x, const double &y)
{
    real = x;
    imag = y;
}

double Phasor::Magnitude() const
{
    return std::sqrt(real * real + imag * imag);
}

double Phasor::Abs() const
{
    return std::sqrt(real * real + imag * imag);
}

double Phasor::Phase() const
{
    return std::atan2(imag, real);
}

double Phasor::Angle() const
{
    return std::atan2(imag, real);
}

double Phasor::PhaseDeg() const
{
    double angle_deg = 180 * Phase() / M_PI;
    if (angle_deg > 180.0) {
        angle_deg = 180.0;
    } else if (angle_deg <= -180.0) {
        angle_deg = 180.0;
    }
    return angle_deg;
}

double Phasor::AngleDeg() const
{
    double angle_deg = 180 * Phase() / M_PI;
    if (angle_deg > 180.0) {
        angle_deg = 180.0;
    } else if (angle_deg <= -180.0) {
        angle_deg = 180.0;
    }
    return angle_deg;
}

double Phasor::Real() const
{
    return real;
}

double Phasor::Imag() const
{
    return imag;
}

Phasor Phasor::operator+(const Phasor &other) const
{
    return Phasor(real + other.Real(), imag + other.Imag(), AlgTag{});
}

Phasor Phasor::operator-(const Phasor &other) const
{
    return Phasor(real - other.Real(), imag - other.Imag(), AlgTag{});
}

Phasor Phasor::operator*(const Phasor &other) const
{
    return Phasor(real * other.Real() - imag * other.Imag(), real * other.Imag() + imag * other.Real(), AlgTag{});
}

Phasor Phasor::operator/(const Phasor &other) const
{
    double denominator = other.Real() * other.Real() + other.Imag() * other.Imag();
    return Phasor((real * other.Real() + imag * other.Imag()) / denominator, (imag * other.Real() - real * other.Imag()) / denominator, AlgTag{});
}

Phasor Phasor::operator-() const
{
    return Phasor(-real, -imag, AlgTag{});
}

Phasor& Phasor::operator+=(const Phasor &other)
{
    real += other.Real();
    imag += other.Imag();
    return *this;
}

Phasor& Phasor::operator-=(const Phasor &other)
{
    real -= other.Real();
    imag -= other.Imag();
    return *this;
}

Phasor& Phasor::operator*=(const Phasor &other)
{
    SetCartesian(real * other.Real() - imag * other.Imag(), real * other.Imag() + imag * other.Real());
    return *this;
}

Phasor& Phasor::operator/=(const Phasor &other)
{
    double denominator = other.Real() * other.Real() + other.Imag() * other.Imag();
    SetCartesian((real * other.Real() + imag * other.Imag()) / denominator, (imag * other.Real() - real * other.Imag()) / denominator);
    return *this;
}

bool Phasor::operator==(const Phasor &other) const
{
    const double EPSILON = 1e-9; 
    return (std::abs(real - other.Real()) < EPSILON && std::abs(imag - other.Imag()) < EPSILON);
}

bool Phasor::operator!=(const Phasor &other) const
{
    return !(*this == other);
}

Phasor Phasor::Conj() const
{
    return Phasor(real, -imag, AlgTag{});
}

Phasor Phasor::Inv() const
{
    double mag_sq = Magnitude() * Magnitude();
    if (mag_sq == 0.0) {
        return Phasor(0.0, 0.0, AlgTag{});
    } else {
        return Phasor(real / mag_sq, -imag / mag_sq, AlgTag{});
    }
}

Phasor MakePhasorCartesian(double real, double imag)
{
    return Phasor(real, imag, AlgTag{});
}

Phasor MakePhasorPolar(double amplitude, double phase)
{
    return Phasor(amplitude, phase, ExpTag{});
}

Phasor MakePhasorPolarDeg(double amplitude, double phase_deg)
{
    return Phasor(amplitude, phase_deg, DegTag{});
}

Phasor operator+(const Phasor &p, double scalar)
{
    return Phasor(p.Real() + scalar, p.Imag(), AlgTag{});
}

Phasor operator+(double scalar, const Phasor &p)
{
    return Phasor(p.Real() + scalar, p.Imag(), AlgTag{});
}

Phasor operator-(const Phasor &p, double scalar)
{
    return Phasor(p.Real() - scalar, p.Imag(), AlgTag{});
}

Phasor operator-(double scalar, const Phasor &p)
{
    return Phasor(scalar - p.Real(), -p.Imag(), AlgTag{});
}

Phasor operator*(const Phasor &p, double scalar)
{
    return Phasor(p.Magnitude() * scalar, p.Phase(), ExpTag{});
}

Phasor operator*(double scalar, const Phasor &p)
{
    return Phasor(p.Magnitude() * scalar, p.Phase(), ExpTag{});
}

Phasor operator/(const Phasor &p, double scalar)
{
    return Phasor(p.Magnitude() / scalar, p.Phase(), ExpTag{});
}

Phasor operator/(double scalar, const Phasor &p)
{
    return Phasor(scalar / p.Magnitude(), -p.Phase(), ExpTag{});
}

std::ostream& operator<<(std::ostream& os, const Phasor& phasor){
    os << std::fixed << std::setprecision(3) << phasor.Magnitude() << "*e(j*" << phasor.PhaseDeg() << ") ";
    os << "[" << phasor.Real() << " + j*" << phasor.Imag() << "]";
    return os;
}

