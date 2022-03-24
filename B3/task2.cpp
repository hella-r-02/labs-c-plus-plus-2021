#include <iostream>
#include <algorithm>

#include "factorialContainer.hpp"

void task2(std::ostream &out)
{
  FactorialContainer factorial(10);
  std::copy(factorial.begin(), factorial.end(), std::ostream_iterator<size_t>(out, " "));
  out << "\n";

  std::reverse_copy(factorial.begin(), factorial.end(), std::ostream_iterator<size_t>(out, " "));
  out << "\n";
}
