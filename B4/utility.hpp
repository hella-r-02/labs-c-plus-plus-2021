#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <istream>

class Separator
{
public:
  Separator(const char value = ',');

private:
  char value_;
  friend std::istream &operator>>(std::istream &inStream, Separator &separator);
};

class StreamGuard
{
public:
  StreamGuard(std::istream &in);
  ~StreamGuard();
private:
  std::istream &stream_;
  std::istream::fmtflags flags_;
};

std::istream &skip_ws(std::istream &in);

#endif
