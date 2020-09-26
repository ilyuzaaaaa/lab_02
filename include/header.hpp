// Copyright 2018 Your Name <your_email>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_
#include <cstddef>

#include <ctime> // содержит time()
#include <cstdlib> // содержит srand() и rand()
#include <string>
#include <time.h>
#include <numeric>
#include <algorithm>
#include <random>
#include <iostream>
//#include <GL/glut.h>




class Cache {
  int *array;
  size_t size;
 public:
  Cache(size_t const &size);

  static std::vector <int>  amountOfExperiments();

  double firstToEnd();

  double endToFirst();

  double randomWay();

  static void resultWindow(std::string const &travelVariant, size_t const &numberOfExperiment,
                           int const &size, double const &timeOfArray);
  void Run();

  ~Cache();
};
#endif // INCLUDE_HEADER_HPP_
