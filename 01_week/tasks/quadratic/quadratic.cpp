#include <iostream>
#include <cmath>
#include <iomanip>
#include <algorithm> // Для std::min и std::max


void SolveQuadratic(int a, int b, int c) {
    if (a == 0) {
        if (b == 0) {
            if (c == 0) {
                std::cout << "infinite solutions";
            } else {
                std::cout << "no solutions";
            }
        } else {
            double x = static_cast<double>(-c) / b;
            std::cout << std::defaultfloat << std::setprecision(6) << x;
        }
    } else {
        long long discriminant = static_cast<long long>(b) * b - 4 * static_cast<long long>(a) * c;

        if (discriminant > 0) {
            double x1 = (-b - std::sqrt(static_cast<double>(discriminant))) / (2 * a);
            double x2 = (-b + std::sqrt(static_cast<double>(discriminant))) / (2 * a);
            std::cout << std::defaultfloat << std::setprecision(6) << std::min(x1, x2);
            std::cout << " ";
            std::cout << std::defaultfloat << std::setprecision(6) << std::max(x1, x2);
        } else if (discriminant == 0) {
            double x = static_cast<double>(-b) / (2 * a);
            std::cout << std::defaultfloat << std::setprecision(6) << x;
        } else {
            std::cout << "no solutions";
        }
    }
}