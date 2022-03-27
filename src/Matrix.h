#include <iostream>
#include <vector>
#include <cassert>
#include <random>
#include <utility>
#include <time.h>

#include "MatrixProduct.h"

#pragma once

class Matrix {
  public:
    Matrix() {}
    Matrix(unsigned n, unsigned m);
    Matrix(raw_matrix matrix);
    ~Matrix();

    unsigned get_n();
    unsigned get_m();
    int at(std::pair<int, int> position) {return matrix_[position.first][position.second];}
    std::vector<int>& operator[](unsigned idx);
    std::vector<int> operator[](unsigned idx) const;
    Matrix operator+(Matrix matrix_b);
    Matrix operator-(Matrix matrix_b);
    Matrix operator*(Matrix matrix_b);
    void DefineProductAlgorithm(char algorithm_type);

  private:
    Matrix Product(Matrix matrix_b);

    raw_matrix matrix_;
    MatrixProduct *product_algorithm_{nullptr};
    unsigned n_rows_;
    unsigned n_columns_;
};