#include "data-struct.hpp"

#include "utility.hpp"

const char SEPARATOR = ',';
const int valueBoundariesKey = 5;

int readKey(std::istream &in)
{
  int key;
  in >> skip_ws >> key;
  if (!in || std::abs(key) > valueBoundariesKey)
  {
    in.setstate(std::ios::failbit);
    return 0;
  }
  return key;
}

std::string readStr(std::istream &in)
{
  std::string str;
  std::getline(in, str);
  if (!in || str.empty())
  {
    in.setstate(std::ios::failbit);
    return "";
  }
  return str;
}

std::istream &operator>>(std::istream &in, DataStruct &dataStruct)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  StreamGuard guard(in);
  in >> std::noskipws;
  const int key1 = readKey(in);
  if (!in)
  {
    return in;
  }
  Separator separator1(SEPARATOR);
  if (!(in >> skip_ws >> separator1))
  {
    return in;
  }
  in >> skip_ws;
  const int key2 = readKey(in);
  if (!in)
  {
    return in;
  }
  Separator separator2(SEPARATOR);
  if (!(in >> skip_ws >> separator2))
  {
    return in;
  }
  in >> skip_ws;
  const std::string str = readStr(in);

  if (!in)
  {
    return in;
  }
  dataStruct = {key1, key2, str};

  return in;
}

bool Comparator::operator()(const DataStruct &left, const DataStruct &right)
{
  if (left.key1 != right.key1)
  {
    return (left.key1 < right.key1);
  }
  if (left.key2 != right.key2)
  {
    return (left.key2 < right.key2);
  }
  return (left.str.length() < right.str.length());
}

std::ostream &operator<<(std::ostream &out, const DataStruct &dataStruct)
{
  std::ostream::sentry sentry(out);
  if (sentry)
  {
    out << dataStruct.key1 << SEPARATOR << dataStruct.key2 << SEPARATOR << dataStruct.str << "\n";
  }
  return out;
}
