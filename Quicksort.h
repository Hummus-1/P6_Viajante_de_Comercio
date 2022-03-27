#pragma once

#include <iostream>

#include "DivideAndConquer.h"

namespace DC {

template<class T>
struct QSData {
  QSData(std::vector<T>* seq, int s, int e) : sequence(seq), start(s), end(e) {}
  std::vector<T>* sequence;
  int start, end;
};

template<class T>
class Quicksort : public DivideAndConquer<QSData<T>, QSData<T>> {
  public:
    Quicksort() {this->division_factor_ = 2;}
    ~Quicksort() {}

    QSData<T> Solve(std::vector<int>& sequence) {
      return this->SolveProblem(*(new QSData<T>(&sequence, 0, sequence.size() - 1)));
    }
  private:
  bool Small(QSData<T> problem) {
    return problem.start >= problem.end;
  }

  QSData<T> SolveSmall(QSData<T> problem) {
    return problem;
  }

  void swapElements(std::vector<int>& vector_to_swap, int i, int j) {
    int temp = vector_to_swap[i];
    vector_to_swap[i] = vector_to_swap[j];
    vector_to_swap[j] = temp;
  };

  std::vector<QSData<T>> Divide(QSData<T> problem) {
    int start = problem.start, end = problem.end;
    int pivot = problem.sequence->at((problem.start + problem.end) / 2);
    while (start <= end) {
      while (problem.sequence->at(start) < pivot) start++;
      while (problem.sequence->at(end) > pivot) end--;
      if (start <= end) {
      std::swap(problem.sequence->at(start), problem.sequence->at(end));
      start++;
      end--;
      }
    }
    std::vector<QSData<T>> divided_problem;
    divided_problem.emplace_back(*(new QSData<T>(problem.sequence, problem.start, end)));
    divided_problem.emplace_back(*(new QSData<T>(problem.sequence, start, problem.end)));
    return divided_problem;
  }

  QSData<T> CombinePreparation(std::vector<QSData<T>> divided_solution) {
    return Combine(divided_solution[0], divided_solution[1]);
  }

  QSData<T> Combine(QSData<T> s1, QSData<T> s2) {
    return *(new QSData<T>(s1.sequence, s1.start, s2.end));
  }

  std::string getA() {
    return "2";
  }

  std::string getB() {
    return "n/2";
  }

  std::string getC() {
    return "n";
  }
};

}