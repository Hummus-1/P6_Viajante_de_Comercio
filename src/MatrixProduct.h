#include <iostream>
#include <vector>

#pragma once

typedef std::vector<std::vector<int> > raw_matrix;

class MatrixProduct {
  public: 
	  virtual raw_matrix AlgorithmInterface(raw_matrix matrix_a, raw_matrix matrix_b) = 0;
    raw_matrix CreateEmpty(unsigned rows, unsigned columns);
 };


// A 'ConcreteStrategy' class
class MatrixProductR : public MatrixProduct  {
  public:
    raw_matrix AlgorithmInterface(raw_matrix matrix_a, raw_matrix matrix_b);
  private:
    raw_matrix Product(raw_matrix matrix_a, raw_matrix matrix_b);
};

 
// A 'ConcreteStrategy' class
class MatrixProductC : public MatrixProduct  {
  public:
    raw_matrix AlgorithmInterface(raw_matrix matrix_a, raw_matrix matrix_b);
  private:
    raw_matrix Product(raw_matrix matrix_a, raw_matrix matrix_b);
};