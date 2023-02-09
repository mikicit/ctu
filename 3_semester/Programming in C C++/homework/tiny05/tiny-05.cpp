#include "tiny-05.hpp"

namespace pjc {
    complex::complex(double real, double imaginary) :
        m_real(real),
        m_imag(imaginary) {}

    double complex::real() const {
        return m_real;
    }

    void complex::real(double d) {
        m_real = d;
    }

    double complex::imag() const {
        return m_imag;
    }

    void complex::imag(double d) {
        m_imag = d;
    }

    complex complex::operator+(const complex &rhs) const {
        return {m_real + rhs.m_real, m_imag + rhs.m_imag};
    }

    complex complex::operator+(const double &rhs) const {
        return {m_real + rhs, m_imag};
    }

    complex operator+(const double &lhs, const complex &rhs) {
        return {rhs.m_real + lhs, rhs.m_imag};
    }

    complex complex::operator-(const complex &rhs) const {
        return {m_real - rhs.m_real, m_imag - rhs.m_imag};
    }

    complex complex::operator-(const double &rhs) const {
        return {m_real - rhs, m_imag};
    }


    complex operator-(const double &lhs, const complex &rhs) {
        return {lhs - rhs.m_real, 0 - rhs.m_imag};
    }

    complex complex::operator*(const complex &rhs) const {
        return {(m_real * rhs.m_real) - (m_imag * rhs.m_imag), (m_real * rhs.m_imag) + (m_imag * rhs.m_real)};
    }

    complex complex::operator*(const double &rhs) const {
        return {m_real * rhs, m_imag * rhs};
    }

    complex operator*(const double &lhs, const complex &rhs) {
        return {lhs * rhs.m_real, lhs * rhs.m_imag};
    }

    complex complex::operator/(const complex &rhs) const {
        return {
            ((m_real * rhs.m_real) + (m_imag * rhs.m_imag)) / ((rhs.m_real * rhs.m_real) + (rhs.m_imag * rhs.m_imag)),
            ((rhs.m_real * m_imag) - (m_real * rhs.m_imag)) / ((rhs.m_real * rhs.m_real) + (rhs.m_imag * rhs.m_imag))};
    }

    complex complex::operator/(const double &rhs) const {
        return {
                (m_real * rhs) / (rhs * rhs),
                (rhs * m_imag) / (rhs * rhs)};
    }

    complex operator/(const double &lhs, const complex &rhs) {
        return {
                ((lhs * rhs.m_real)) / ((rhs.m_real * rhs.m_real) + (rhs.m_imag * rhs.m_imag)),
                ((lhs * rhs.m_imag)) / ((rhs.m_real * rhs.m_real) + (rhs.m_imag * rhs.m_imag))};
    }
}
