#include <stdexcept>
#include <functional>
#include <vector>
#include <list>

#include "sort.hpp"
#include "access.hpp"

void taskOne(std::function<bool(const int &, const int &)> cmp)
{
  std::vector<int> vector;
  int i = 0;
  while (std::cin >> i)
  {
    vector.push_back(i);
  }
  if (!std::cin.eof())
  {
    throw std::invalid_argument("Non-correct data");
  }
  if (vector.empty())
  {
    return;
  }
  std::vector<int> vector2(vector);
  std::list<int> list(vector.begin(), vector.end());

  sort<AccessByOperator>(vector, cmp);
  sort<AccessByAt>(vector2, cmp);
  sort<AccessByIterator>(list, cmp);
  print(vector, " ", std::cout);
  std::cout << "\n";
  print(vector2, " ", std::cout);
  std::cout << "\n";
  print(list, " ", std::cout);
}
