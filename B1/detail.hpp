#ifndef DETAIL_HPP
#define DETAIL_HPP

#include <iostream>
#include <stdexcept>
#include <cstring>
#include <functional>

template<typename T>
void print(const T &container, const char *separator, std::ostream &out)
{
  if (separator == nullptr)
  {
    throw std::invalid_argument("Invalid print separator");
  }
  for (auto i = container.begin(); i != container.end(); i++)
  {
    out << *i << separator;
  }
}

template<typename T>
std::function<bool(const T &, const T &)> determineOrder(const char *order)
{
  if (order == nullptr)
  {
    throw std::invalid_argument("Parameter missing");
  }
  if (!strcmp(order, "ascending"))
  {
    return std::greater<const T>();
  }
  if (!strcmp(order, "descending"))
  {
    return std::less<const T>();
  }
  throw std::invalid_argument("Wrong parameter");
}

#endif
