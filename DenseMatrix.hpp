//
// Created by d-qql on 22.09.2021.
//

#ifndef VICHMATY1_DENSEMATRIX_HPP
#define VICHMATY1_DENSEMATRIX_HPP


#include <iostream>
#include <vector>
#include <set>
#include "utility/Consts.hpp"
#include "utility/Triplet.hpp"

using elm_t = double;
using idx_t = std::size_t;

class DenseMatrix {
public:

private:

    idx_t H{}, W{};
    std::vector<elm_t> matrix;

public:

    DenseMatrix() = default;
    DenseMatrix(idx_t h, idx_t w);
    DenseMatrix(idx_t h, idx_t w, const std::set<Triplet> &in);
    elm_t& operator()(const idx_t& i, const idx_t& j);

    elm_t operator()(const idx_t& i, const idx_t& j) const;

    [[nodiscard]] idx_t sizeH() const;
    [[nodiscard]] idx_t sizeW() const;


};
//Обработать исключение несопоставимых размеров
std::vector<double> operator*(const DenseMatrix &M, const std::vector<double> &vec);

std::ostream& operator<<(std::ostream& os, const DenseMatrix& M);

std::vector<double> ThomasAlgorithm(const DenseMatrix& A, const std::vector<double>& B);

#endif //VICHMATY1_DENSEMATRIX_HPP
