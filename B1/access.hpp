#ifndef ACCESS_HPP
#define ACCESS_HPP

#include <iostream>

template <typename T>
struct AccessByOperator
{
  using reference = typename T::reference;
  using iterator = typename T::size_type;

  static iterator getBegin(const T&)
  {
    return 0;
  }

  static iterator getEnd(const T& collection)
  {
    return collection.size();
  }

  static reference getElement(T& collection, iterator index)
  {
    return collection[index];
  }
};

template <typename T>
struct AccessByAt
{
  using reference = typename T::reference;
  using iterator = typename T::size_type;

  static iterator getBegin(const T&)
  {
    return 0;
  }

  static iterator getEnd(const T& collection)
  {
    return collection.size();
  }

  static reference getElement(T& collection, iterator index)
  {
    return collection.at(index);
  }
};

template <typename T>
struct AccessByIterator
{
  using reference = typename T::reference;
  using iterator = typename T::iterator;

  static iterator getBegin(T& collection)
  {
    return collection.begin();
  }

  static iterator getEnd(T& collection)
  {
    return collection.end();
  }

  static reference getElement(T&, iterator index)
  {
    return *index;
  }
};

#endif
