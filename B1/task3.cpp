#include <iostream>
#include <stdexcept>
#include <vector>

#include "detail.hpp"

void taskThree()
{
  std::vector<int> vector;
  int element = 0;
  while (std::cin >> element)
  {
    if (element == 0)
    {
      break;
    }
    vector.push_back(element);
  }
  if ( std::cin.fail() && !std::cin.eof())
  {
    throw std::invalid_argument("Incorrect input");
  }
  if (vector.empty())
  {
    return;
  }
  if (element != 0)
  {
    throw std::invalid_argument("Last data must be zero");
  }
  if (vector.back() == 1)
  {
    auto i = vector.begin();
    while (i != vector.end())
    {
      if (*i % 2 == 0)
      {
        i = vector.erase(i);
      }
      else
      {
        i++;
      }
    }
  }
  else if (vector.back() == 2)
  {
    auto i = vector.begin();
    while (i != vector.end())
    {
      if (*i % 3 == 0)
      {
        i = vector.insert(++i, 3, 1) + 2;
      }
      i++;
    }
  }
  print(vector, " ", std::cout);
}
