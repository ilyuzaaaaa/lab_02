// Copyright 2018 Your Name <your_email>

#include <fstream>
#include <Cache.hpp>

using std::cout;
using std::endl;

struct CacheLines {
  static const size_t FirstLine = 384;  // in KyloBytes
  static const size_t LastLine = 9216;
};
void DoubleUp(int value) { return value * 2; }

int doSomething(int value) { return value; }
std::vector<int> Cache::amountOfExperiments() {
  std::vector<int> experiments;
  experiments.push_back(CacheLines.FirstLine / 2);
  int q = 256;
  static const auto MAX_SIZE = CacheLines.LastLine * 1.5;
  while (q < MAX_SIZE) {
    experiments.push_back(q);
    DoubleUp(q);
  }
  experiments.push_back(MAX_SIZE);
  return experiments;
}

Cache::Cache(size_t const &_size) {
  this->size = _size;
  array = new int[size];
  srand(time(NULL));
  std::mt19937 generator(clock());
  for (size_t i = 0; i < size; ++i) {
    array[i] = generator();
  }
}

double Cache::firstToEnd() {
  for (size_t j = 0; j < size; j++) {
    doSomething(array[j]);
  }
  srand(time(NULL));
  clock_t start = clock();
  for (size_t i = 0; i < iterations; ++i) {
    for (size_t j = 0; j < size; j++) {
      doSomething(array[j]);
    }
  }
  clock_t end = clock();
  return static_cast<double>(end - start) / CLOCKS_PER_SEC;
}

double Cache::endToFirst() {
  for (size_t j = size; j > 0; j--) {
    doSomething(array[j - 1]);
  }
  srand(time(NULL));
  clock_t start = clock();
  for (size_t i = 0; i < iterations; ++i) {
    for (size_t j = size; j > 0; j--) {
      doSomething(array[j - 1]);
    }
  }
  clock_t end = clock();
  return static_cast<double>(end - start) / CLOCKS_PER_SEC;
}

double Cache::randomWay() {
  std::vector<size_t> indexes(size);
  srand(time(NULL));
  std::iota(indexes.begin(), indexes.end(), 0);
  std::shuffle(indexes.begin(), indexes.end(),
               std::mt19937(std::random_device()()));
  for (size_t j = 0; j < size; ++j) {
    doSomething(array[indexes[j]]);
  }
  clock_t start = clock();
  for (size_t i = 0; i < iterations; ++i) {
    for (size_t j = 0; j < size; ++j) {
      doSomething(array[indexes[j]]);
    }
  }
  clock_t end = clock();
  return static_cast<double>(end - start) / CLOCKS_PER_SEC;
}

void Cache::resultWindow(std::string const &travelVariant,
                         size_t const &numberOfExperiment, int const &size,
                         double const &timeOfArray) {
  cout << "   travel_variant: " << travelVariant << endl;
  cout << "   experiments: " << endl;
  cout << "   - experiment: " << endl;
  cout << "       number: " << numberOfExperiment << endl;
  cout << "       input_data: " << endl;
  cout << "buffer_size: " << size << endl;
  cout << "       results: " << endl;
  cout << "           duration: " << timeOfArray << endl;
}

Cache::~Cache() { delete[] array; }

void Cache::Run() {
  int numberOfExperiment = 1;

  std::vector<double> firstToEnd;
  std::vector<double> endToFirst;
  std::vector<double> randomWay;

  std::vector<int> sizeOfArray = Cache::amountOfExperiments();
  static const auto SIZE = 1024 / sizeof(decltype(sizeOfArray)::value_type);
  std::vector<int>::iterator i1 = sizeOfArray.begin();
  std::vector<double>::iterator i2;

  for (; i1 < sizeOfArray.end(); ++i1) {
    cout << "investigation:" << endl;
    Cache experiment(*i1 * SIZE);
    firstToEnd.push_back(experiment.firstToEnd());
    i2 = firstToEnd.end() - 1;
    Cache::resultWindow(" 1 -> end", numberOfExperiment, *i1, *i2);
    endToFirst.push_back(experiment.endToFirst());
    i2 = endToFirst.end() - 1;
    Cache::resultWindow(" End -> 1", numberOfExperiment, *i1, *i2);
    randomWay.push_back(experiment.randomWay());
    i2 = randomWay.end() - 1;
    Cache::resultWindow(" Random ", numberOfExperiment, *i1, *i2);
    numberOfExperiment++;
  }
}
