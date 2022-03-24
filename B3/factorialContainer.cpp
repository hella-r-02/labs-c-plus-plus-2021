#include "factorialContainer.hpp"

#include <stdexcept>

FactorialContainer::const_iterator &FactorialContainer::const_iterator::operator++()
{
  ++number_;
  value_ *= number_;
  return *this;
}

FactorialContainer::const_iterator FactorialContainer::const_iterator::operator++(int)
{
  const_iterator temp = *this;
  ++(*this);
  return temp;
}

FactorialContainer::const_iterator &FactorialContainer::const_iterator::operator--()
{
  if (number_ < 1)
  {
    throw std::out_of_range("Lower bound reached");
  }
  value_ /= (number_);
  number_--;
  return *this;
}

FactorialContainer::const_iterator FactorialContainer::const_iterator::operator--(int)
{
  if (number_ < 1)
  {
    throw std::out_of_range("Lower bound reached");
  }
  const_iterator temp = *this;
  --(*this);
  return temp;
}

bool FactorialContainer::const_iterator::operator!=(const const_iterator &otherIterator) const
{
  return !(*this == otherIterator);
}

bool FactorialContainer::const_iterator::operator==(const const_iterator &otherIterator) const
{
  return (value_ == otherIterator.value_) && (number_ == otherIterator.number_);
}

FactorialContainer::const_iterator::const_iterator() :
  value_(1),
  number_(1)
{}

FactorialContainer::const_iterator::const_iterator(size_t value, size_t number) :
  value_(value),
  number_(number)
{}

FactorialContainer::const_iterator::value_type FactorialContainer::const_iterator::operator*() const
{
  return value_;
}

FactorialContainer::FactorialContainer(size_t size) :
  size_(size),
  factorial_(calculateFactorial(size + 1))
{}

FactorialContainer::const_iterator FactorialContainer::begin() const
{
  return const_iterator();
}

size_t calculateFactorial(size_t number)
{
  size_t temp = 1;
  for (size_t i = 1; i <= number; i++)
  {
    if (temp > SIZE_MAX / i)
    {
      throw std::overflow_error("Factorial value is too large");
    }
    temp *= i;
  }
  return temp;
}

FactorialContainer::const_iterator FactorialContainer::end() const
{
  return const_iterator(factorial_, size_ + 1);
}

FactorialContainer::const_reverse_iterator FactorialContainer::rbegin() const
{
  return std::reverse_iterator<FactorialContainer::const_iterator>(end());
}

FactorialContainer::const_reverse_iterator FactorialContainer::rend() const
{
  return std::reverse_iterator<FactorialContainer::const_iterator>(begin());
}
