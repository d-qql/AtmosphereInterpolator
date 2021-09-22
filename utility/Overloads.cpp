//
// Created by d-qql on 22.09.2021.
//

#include "Overloads.hpp"

std::vector<double> operator*(const double &k, std::vector<double> const &vec) {
    std::vector<double> result;
    result.resize(vec.size());
    for (size_t i = 0; i < result.size(); ++i) {
        result[i] = k * vec[i];
    }
    return result;
}

std::vector<double> operator+(const std::vector<double> &fVec, const std::vector<double> &sVec) {
    std::vector<double> res;
    if (fVec.size() == sVec.size()) {
        res.resize(fVec.size());
        for (size_t i = 0; i < fVec.size(); ++i) {
            res[i] = fVec[i] + sVec[i];
        }
    }
    return res;
}

std::vector<double> operator-(const std::vector<double> &fVec, const std::vector<double> &sVec) {
    std::vector<double> res;
    if (fVec.size() == sVec.size()) {
        res.resize(fVec.size());
        for (size_t i = 0; i < fVec.size(); ++i) {
            res[i] = fVec[i] - sVec[i];
        }
    }
    return res;
}

double operator*(const std::vector<double> &a, const std::vector<double> &b) {
    auto res = static_cast<double>(0);
    for (size_t i = 0; i < a.size(); ++i) {
        res += a[i] * b[i];
    }
    return res;
}

std::ostream &operator<<(std::ostream &os, const std::vector<double> &b) {
    os << "( ";
    for (auto i: b) {
        os << i << " ";
    }
    os << ")\n";
    return os;
}

void printSystem(const DenseMatrix &A, const std::vector<double> &b) {
    for (size_t i = 0; i < A.sizeH(); ++i) {
        for (size_t j = 0; j < A.sizeW(); ++j) {
            std::cout << A(i, j) << " ";
        }
        std::cout << b[i] << std::endl;
    }
}