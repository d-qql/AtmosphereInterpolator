#include <iostream>
#include <set>
#include "DenseMatrix.hpp"
#include "utility/Overloads.hpp"
#include "CubicSpline.hpp"
#include <cmath>
int main() {

    CubicSpline spline("/home/d-qql/CLionProjects/vichmaty1/resources/Atmosphere_1.csv");
    for(int i = 80000; i <= 1200000; ++i){
        if(std::abs(spline.interpolate(i) - 2e-8) < 1e-9) {
            std::cout << "Heihgt: " << i << std::endl;
            break;
        }
    }
    io::CSVReader<2> in("/home/d-qql/CLionProjects/vichmaty1/resources/Atmosphere_2.csv");
    in.read_header(io::ignore_extra_column, "H", "DEN");
    double height, density;
    double max_error = 0;
    double log_max_error = 0;
    double interpolated;
    double log_interpolated = 0;
    double log_error = 0;
    double error = 0;
    while (in.read_row(height, density)) {
        interpolated = spline.interpolate(height);
        log_interpolated = std::log(spline.interpolate(height));
        error = std::abs(density - interpolated) / std::abs(interpolated);
        log_error = std::abs(log(density) - log_interpolated) / std::abs(log_interpolated);
        if (max_error < error) max_error = error;
        if (log_max_error < log_error) log_max_error = log_error;
        //std::cout<<error<<std::endl;
    }
    std::cout << "Max relative error: " << max_error << std::endl;
    std::cout << "Max relative error in log scale: " << log_max_error << std::endl;


    return 0;
}
