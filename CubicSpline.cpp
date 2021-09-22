//
// Created by d-qql on 22.09.2021.
//

#include "CubicSpline.hpp"
#include <iostream>
#include <set>
#include "DenseMatrix.hpp"
#include "utility/Overloads.hpp"
#include <algorithm>
CubicSpline::CubicSpline(const std::string &path_to_csv) {
    io::CSVReader<2> in(path_to_csv);
    in.read_header(io::ignore_extra_column, "H", "DEN");
    double height, density;
    while (in.read_row(height, density)) {
        x.push_back(height);
        y.push_back(density);
        //     std::cout << height << " " << density << std::endl;
    }
    std::set<Triplet> input;
    unsigned int N = static_cast<int>(x.size()) - 1;
    coefs.resize(N);
    input.insert({1, 0, 0}); // c[0]
    input.insert({2, 1, 1}); //c[1]
    input.insert({x[2] / (x[1] + x[2]), 1, 2}); //c[2]
    for (unsigned int i = 2; i < N - 1; ++i) {
        input.insert({2, i, i});
        input.insert({x[i] / (x[i] + x[i + 1]), i, i - 1});
        input.insert({x[i + 1] / (x[i] + x[i + 1]), i, i + 1});
    }
    input.insert({x[N - 1] / (x[N - 1] + x[N]), N - 1, N - 2}); //c[2]
    input.insert({2, N - 1, N - 1}); //c[1]
    input.insert({1, N, N}); // c[N]
    DenseMatrix D(N + 1, N + 1, input);
    std::vector<double> right_part(N + 1);
    right_part[0] = 0;
    right_part[N] = 0;
    for (unsigned int i = 1; i < N; ++i) {
        right_part[i] = 6 * difference3(i + 1);
    }
    // printSystem(D, right_part);
    std::vector<double> c = ThomasAlgorithm(D, right_part);
    for (int i = 0; i < coefs.size(); ++i) {
        coefs[i].c = c[i + 1];
        coefs[i].a = y[i];
        if (i == 0) {
            coefs[i].d = coefs[i].c / (x[i + 1] - x[i]);
            coefs[i].b = coefs[i].c / 3. * (x[i + 1] - x[i]) + difference2(0, 1);
        } else {
            coefs[i].d = (c[i + 1] - c[i]) / (x[i + 1] - x[i]);
            coefs[i].b = c[i + 1] / 3. * (x[i + 1] - x[i]) + difference2(i, i + 1);
        }
    }
}

double CubicSpline::difference2(unsigned int i, unsigned int j) const {
    return (y[j] - y[i]) / (x[j] - x[i]);
}

double CubicSpline::difference3(unsigned int i) const {
    return (difference2(i - 1, i) - difference2(i - 2, i - 1)) / (x[i] - x[i - 2]);
}

double CubicSpline::interpolate(double t) const {
    int i = std::upper_bound(x.begin(), x.end(), t) - x.begin() - 1;
    if(std::abs(t - x.back()) < 1e-10) return y.back();
    return coefs[i].a + coefs[i].b * (t - x[i]) + coefs[i].c * (t - x[i]) * (t - x[i]) +
           coefs[i].d * (t - x[i]) * (t - x[i]) * (t - x[i]);
}



