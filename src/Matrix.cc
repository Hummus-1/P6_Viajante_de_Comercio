#include "Matrix.h"

Matrix::Matrix(unsigned n, unsigned m) {
  time_t t;
  n_rows_ = n;
  n_columns_ = m;
  srand((unsigned) time(&t));
  matrix_.resize(n_rows_);
  for(unsigned i = 0; i < n; ++i) {
    matrix_[i].resize(n_columns_);
    for(unsigned j = 0; j < m; ++j) {
      matrix_[i][j] = rand() % 100 + 1;
    }
  }
}

Matrix::Matrix(raw_matrix matrix) {
  n_rows_ = matrix.size();
  n_columns_ = matrix[0].size();
  matrix_ = matrix;
}

Matrix::~Matrix() {
  
}

unsigned Matrix::get_n() {
  return n_rows_;
}

unsigned Matrix::get_m() {
  return n_columns_;
}

std::vector<int>& Matrix::operator[](unsigned idx) {
  return matrix_[idx];
}

std::vector<int> Matrix::operator[](unsigned idx) const {
  return matrix_[idx];
}

void Matrix::DefineProductAlgorithm(char algorithm_type) {
  if(algorithm_type == 'R') {
    product_algorithm_ = new MatrixProductR();
  }
  else if(algorithm_type == 'C') {
    product_algorithm_ = new MatrixProductC();
  }
  else {
    std::cout << "Unrecognized algorithm type. Should be R or C.\n";
  }
}

Matrix Matrix::Product(Matrix matrix_b) {
  if(product_algorithm_ == nullptr) {
    throw std::bad_exception();
  }
  return product_algorithm_->AlgorithmInterface(matrix_, matrix_b.matrix_);
}

Matrix Matrix::operator*(Matrix matrix_b) {
  try {
    return *new Matrix(Product(matrix_b));
  }
  catch (const std::out_of_range& e) {
    std::cout << "ERROR: Can't operate this two matrices due to their size.\n";
  }
  catch (const std::bad_exception& e) {
    std::cout << "ERROR: Product algorithm not defined.\n";
  }
  return *new Matrix(matrix_);
}

Matrix Matrix::operator+(Matrix matrix_b) {
  int n = (n_rows_ > matrix_b.get_n()) ? n_rows_ : matrix_b.get_n();
  int m = (n_columns_ > matrix_b.get_m()) ? n_columns_ : matrix_b.get_m();
  Matrix result(n, m);
  try {
    for(int i = 0; i < n; ++i) {
      for(int j = 0; i < m; ++j) {
        result[i][j] = matrix_[i][j] + matrix_b[i][j];
      }
    }
  }
  catch (const std::out_of_range& e) {
    std::cout << "ERROR: Can't operate this two matrices due to their size.\n";
  }
  catch (const std::bad_exception& e) {
    std::cout << "ERROR: Product algorithm not defined.\n";
  }
  return result;
}

Matrix Matrix::operator-(Matrix matrix_b) {
  int n = (n_rows_ > matrix_b.get_n()) ? n_rows_ : matrix_b.get_n();
  int m = (n_columns_ > matrix_b.get_m()) ? n_columns_ : matrix_b.get_m();
  Matrix result(n, m);
  try {
    for(int i = 0; i < n; ++i) {
      for(int j = 0; i < m; ++j) {
        result[i][j] = matrix_[i][j] - matrix_b[i][j];
      }
    }
  }
  catch (const std::out_of_range& e) {
    std::cout << "ERROR: Can't operate this two matrices due to their size.\n";
  }
  catch (const std::bad_exception& e) {
    std::cout << "ERROR: Product algorithm not defined.\n";
  }
  return result;
}

void Matrix::resize(unsigned n, unsigned m) {
  n_rows_ = n;
  n_columns_ = m;
  matrix_.resize(n_rows_);
  for(unsigned i = 0; i < n; ++i) {
    matrix_[i].resize(n_columns_);
  }
}