//
// Created by d-qql on 22.09.2021.
//

#ifndef VICHMATY1_OVERLOADS_HPP
#define VICHMATY1_OVERLOADS_HPP
#include <vector>
#include "../DenseMatrix.hpp"

std::vector<double> operator*(const double &k, std::vector<double> const &vec);

std::vector<double> operator+(const std::vector<double>& fVec, const std::vector<double>& sVec);

std::vector<double> operator-(const std::vector<double>& fVec, const std::vector<double>& sVec);

double operator*(const std::vector<double>& a, const std::vector<double>& b);

std::ostream& operator<<(std::ostream& os, const std::vector<double>& b);

void printSystem(const DenseMatrix &A, const std::vector<double> &b);
#endif //VICHMATY1_OVERLOADS_HPP
