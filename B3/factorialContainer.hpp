#ifndef FACTORIALCONTAINER_HPP
#define FACTORIALCONTAINER_HPP

#include <iostream>
#include <iterator>
#include <cstddef>

class FactorialContainer
{
public:
  class const_iterator: public std::iterator<std::bidirectional_iterator_tag, size_t, std::ptrdiff_t, size_t, size_t>
  {

  public:
    value_type operator*() const;
    const_iterator &operator++();
    const_iterator &operator--();
    const_iterator operator++(int);
    const_iterator operator--(int);

    bool operator!=(const const_iterator &otherIterator) const;
    bool operator==(const const_iterator &otherIterator) const;

  private:
    const_iterator();
    const_iterator(value_type value, size_t number);
    friend FactorialContainer;
    value_type value_;
    size_t number_;
  };

  using const_reverse_iterator = std::reverse_iterator<const_iterator>;
  explicit FactorialContainer(size_t size = 0);
  const_iterator begin() const;
  const_iterator end() const;
  const_reverse_iterator rbegin() const;
  const_reverse_iterator rend() const;

private:
  size_t size_;
  size_t factorial_;
};
size_t calculateFactorial(size_t number);
#endif
