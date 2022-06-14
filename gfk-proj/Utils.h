#pragma once
#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include <Eigen/Dense>
#include <sstream>
#include <string>
#include <numbers>


namespace utils
{
    constexpr double pi = std::numbers::pi;

    template<typename T>
    std::string to_string_with_precision(const T a_value, const int n=6)
    {
        std::ostringstream out;
        out.precision(n);
        out << std::fixed << a_value;
        return out.str();
    }
    double mapInterval(double start1, double stop1, double start2, double stop2, double value);
    sf::Color HSVtoRGB(float H, float S = 1.0, float V = 1.0);
    double distanceBetweenPoints(Eigen::Vector4d& camPos, Eigen::Vector4d& point);
};
