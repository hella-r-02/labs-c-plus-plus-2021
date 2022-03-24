#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <vector>

#include "detail.hpp"
#include "sort.hpp"

void fillRandom(double *array, int size)
{
  if (array == nullptr)
  {
    throw std::invalid_argument("Wrong array");
  }
  if (size <= 0)
  {
    throw std::invalid_argument("Error size");
  }
  for (int i = 0; i < size; i++)
  {
    array[i] = static_cast<double> (rand()) / RAND_MAX * 2 - 1;
  }
}

void taskFour(std::function<bool(const double &, const double &)> cmp, size_t size)
{
  if (size == 0)
  {
    throw std::invalid_argument("Invalid length");
  }

  std::vector<double> vector(size, 0);
  fillRandom(&vector[0], size);
  print(vector, " ", std::cout);
  std::cout << "\n";

  sort<AccessByIterator>(vector, cmp);
  print(vector, " ", std::cout);
}
