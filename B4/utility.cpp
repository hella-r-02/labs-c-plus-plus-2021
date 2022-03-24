#include "utility.hpp"

Separator::Separator(const char value) :
  value_(value)
{
}

std::istream &operator>>(std::istream &in, Separator &separator)
{
  char tempValue;
  if (in.get(tempValue) && tempValue == separator.value_)
  {
    separator.value_ = tempValue;
  }
  else
  {
    in.setstate(std::ios::failbit);
    in.unget();
  }
  return in;
}

StreamGuard::StreamGuard(std::istream &in) :
  stream_(in),
  flags_(in.flags())
{
}

StreamGuard::~StreamGuard()
{
  stream_.setf(flags_);
}

std::istream &skip_ws(std::istream &in)
{
  while (std::isblank(in.peek()))
  {
    in.ignore();
  }
  return in;
}
