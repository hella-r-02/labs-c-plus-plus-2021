#ifndef SORT_HPP
#define SORT_HPP

#include <algorithm>

#include "detail.hpp"
#include "access.hpp"

template<template<typename> class Access, typename Container>
void sort(Container &container, std::function<bool(typename Container::value_type,
    typename Container::value_type)> compare)
{
  using TypeAccess = Access<Container>;
  for (auto i = TypeAccess::getBegin(container); i != TypeAccess::getEnd(container); i++)
  {
    for (auto j = i; j != TypeAccess::getEnd(container); j++)
    {
      if (compare(TypeAccess::getElement(container, i), TypeAccess::getElement(container, j)))
      {
        std::swap(TypeAccess::getElement(container, i), TypeAccess::getElement(container, j));
      }
    }
  }
}

#endif
