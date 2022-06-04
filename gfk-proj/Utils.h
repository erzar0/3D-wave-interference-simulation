#pragma once
#define SFML_STATIC
#include <sstream>
#include <string>
#include <iostream>

namespace utils
{
    template<typename T>
    std::string to_string_with_precision(const T a_value, const int n=6)
    {
        std::ostringstream out;
        out.precision(n);
        out << std::fixed << a_value;
        return out.str();
    }

    double mapInterval(double start1, double stop1, double start2, double stop2, double value);

};
