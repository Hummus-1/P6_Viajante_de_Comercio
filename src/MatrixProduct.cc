#include "MatrixProduct.h"

raw_matrix MatrixProduct::CreateEmpty(unsigned rows, unsigned columns) {
  raw_matrix empty_matrix;
  empty_matrix.resize(rows);
  for(unsigned i = 0; i < rows; ++i) {
    empty_matrix[i].resize(columns);
    for(unsigned j = 0; j < columns; ++j) {
      empty_matrix[i][j] = 0;
    }
  }
  return empty_matrix;
}

raw_matrix MatrixProductR::AlgorithmInterface(raw_matrix matrix_a, raw_matrix matrix_b) {
  return Product(matrix_a, matrix_b);
}

raw_matrix MatrixProductR::Product(raw_matrix matrix_a, raw_matrix matrix_b) {
  raw_matrix product = CreateEmpty( matrix_a.size(), matrix_b[0].size());
  for(unsigned i = 0; i < matrix_a.size(); ++i) {
    for(unsigned j = 0; j < matrix_b[0].size(); ++j) {
      for(unsigned k = 0; k < matrix_b.size(); ++k) {
        product[i][j] += matrix_a[i][k] * matrix_b[k][j];
      }
    }
  }
  return product;
}
 
raw_matrix MatrixProductC::AlgorithmInterface(raw_matrix matrix_a, raw_matrix matrix_b) {
  return Product(matrix_a, matrix_b);
}

raw_matrix MatrixProductC::Product(raw_matrix matrix_a, raw_matrix matrix_b) {
  raw_matrix product = CreateEmpty( matrix_a.size(), matrix_b[0].size());
  for(unsigned i = 0; i < matrix_b[0].size(); ++i) {
    for(unsigned j = 0; j < matrix_a.size(); ++j) {
      for(unsigned k = 0; k < matrix_a[0].size(); ++k) {
        product[j][i] += matrix_a[j][k] * matrix_b[k][i]; 
      }
    }
  }
  return product;
}