//
// Created by d-qql on 22.09.2021.
//

#include "DenseMatrix.hpp"

DenseMatrix::DenseMatrix(idx_t h, idx_t w) : H(h), W(w) {
    matrix.resize(H * W);
}
DenseMatrix::DenseMatrix(idx_t h, idx_t w, const std::set<Triplet> &in): H(h), W(w) {
    matrix.resize(H * W);
    for(auto elm: in){
        matrix[elm.i * W + elm.j] = elm.value;
    }
}
elm_t& DenseMatrix::operator()(const idx_t& i, const idx_t& j){
    return matrix[i*W + j];
}
elm_t DenseMatrix::operator()(const idx_t& i, const idx_t& j) const{
    return matrix[i*W + j];
}
idx_t DenseMatrix::sizeH() const {
    return H;
}
idx_t DenseMatrix::sizeW() const {
    return W;
}
std::vector<double> operator*(const DenseMatrix &M, const std::vector<double> &vec){
    std::vector<double> res;
    res.resize(M.sizeH());
    for(size_t i = 0; i < M.sizeH(); ++i){
        for(size_t j = 0; j < M.sizeW(); ++j){
            res[i]+=M(i,j)*vec[j];
        }
    }
    return res;
}
std::ostream& operator<<(std::ostream& os, const DenseMatrix& M){
    for(size_t i = 0; i < M.sizeH(); ++i){
        for(size_t j = 0; j<M.sizeW(); ++j){
            os<<M(i, j)<<" ";
        }
        os<<std::endl;
    }
    return os;
}
std::vector<double> ThomasAlgorithm(const DenseMatrix& A, const std::vector<double>& B){

    idx_t N = B.size();
    std::vector<double> a(N);
    std::vector<double> b(N);
    std::vector<double> res(N);

    //Прямой ход метода
    double y = A(0, 0);
    try {
        if (std::abs(y) < tolerance) throw "Метод ThomasAlgo не сходится.";
    } catch (char *str){
        std::cout<<str<<std::endl;
    }
    a[0] = -A(0, 1) / y;
    b[0] = B[0] / y;

    for(idx_t i = 1; i < N-1; ++i){
        try{
            y = A(i, i) + A(i, i-1) * a[i-1];
            if (std::abs(y) < tolerance) throw "Метод ThomasAlgo не сходится.";
        } catch (char *str) {
            std::cout<<str<<std::endl;
        }
        a[i] = -A(i, i+1) / y;
        b[i] = (B[i] - A(i, i-1) * b[i-1]) / y;
    }

    //Обратный ход метода
    res[N-1] = (B[N-1] - A(N-1, N-2) * b[N-2]) /
               (A(N-1, N-1) + A(N-1, N-2) * a[N-2]);

    for(int i = static_cast<int>(N)-2; i >= 0; --i){
        res[i] = a[i] * res[i+1] + b[i];
    }
    return res;
}
