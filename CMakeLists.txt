cmake_minimum_required(VERSION 3.20)
project(vichmaty1)

set(CMAKE_CXX_STANDARD 17)

add_executable(vichmaty1 main.cpp DenseMatrix.cpp DenseMatrix.hpp CubicSpline.cpp CubicSpline.hpp utility/Triplet.hpp utility/Consts.hpp utility/Overloads.hpp utility/Overloads.cpp)
target_link_libraries(vichmaty1 -lpthread)