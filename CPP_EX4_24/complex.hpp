#pragma once

#include <iostream>
#include <sstream>

/**
 * @class Complex
 * @brief Represents a complex number with real and imaginary parts.
 */
class Complex {
private:
    double real;  ///< The real part of the complex number.
    double imag;  ///< The imaginary part of the complex number.

public:
    /**
     * @brief Constructor to initialize the complex number.
     * @param r The real part.
     * @param i The imaginary part.
     */
    Complex(double r = 0.0, double i = 0.0) : real(r), imag(i) {}

    /**
     * @brief Addition operator for complex numbers.
     * @param other The other complex number to add.
     * @return The result of the addition.
     */
    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }

    /**
     * @brief Subtraction operator for complex numbers.
     * @param other The other complex number to subtract.
     * @return The result of the subtraction.
     */
    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, imag - other.imag);
    }

    /**
     * @brief Equality operator for complex numbers.
     * @param other The other complex number to compare.
     * @return True if the numbers are equal, false otherwise.
     */
    bool operator==(const Complex& other) const {
        return real == other.real && imag == other.imag;
    }

    /**
     * @brief Converts the complex number to a string.
     * @return The string representation of the complex number.
     */
    std::string to_string() const {
        std::ostringstream oss;
        oss << real << " + " << imag << "i";
        return oss.str();
    }

    /**
     * @brief Get the real part of the complex number.
     * @return The real part.
     */
    double get_real() const { return real; }

    /**
     * @brief Get the imaginary part of the complex number.
     * @return The imaginary part.
     */
    double get_imag() const { return imag; }

    /**
     * @brief Stream insertion operator for complex numbers.
     * @param os The output stream.
     * @param c The complex number to insert.
     * @return The output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
        os << c.real << " + " << c.imag << "i";
        return os;
    }
};
