//
// Created by d-qql on 22.09.2021.
//

#ifndef VICHMATY1_CUBICSPLINE_HPP
#define VICHMATY1_CUBICSPLINE_HPP

#include <string>
#include <vector>
#include "csv.hpp"

struct splineCoefs {
    double a;
    double b;
    double c;
    double d;
};

class CubicSpline {
private:
    std::vector<double> x;
    std::vector<double> y;
    std::vector<splineCoefs> coefs;

    [[nodiscard]] double difference2(unsigned int i, unsigned int j) const;

    [[nodiscard]] double difference3(unsigned int i) const;

public:
    CubicSpline(const std::string &path_to_csv);

    double interpolate(double t) const;
};


#endif //VICHMATY1_CUBICSPLINE_HPP
