// Copyright 2018 Your Name <your_email>

#ifndef INCLUDE_CACHE_HPP_
#define INCLUDE_CACHE_HPP_
#include <time.h>

#include <algorithm>
#include <cstddef>
#include <cstdlib>  // содержит srand() и rand()
#include <ctime>    // содержит time()
#include <iostream>
#include <numeric>
#include <random>
#include <string>
#include <vector>
//#include <GL/glut.h>

class Cache {
  int *array;
  size_t size;

 public:
  explicit Cache(size_t const &size);

  static std::vector<int> amountOfExperiments();

  double firstToEnd();

  double endToFirst();

  double randomWay();

  static void resultWindow(std::string const &travelVariant,
                           size_t const &numberOfExperiment, int const &size,
                           double const &timeOfArray);
  void Run();

  ~Cache();
};
#endif  // INCLUDE_CACHE_HPP_
