#include "dataStruct.hpp"

const char SEPARATOR = ',';

int readKey(std::istream &in)
{
  int key;
  in >>std::skipws>> key;
  if (!in)
  {
    in.setstate(std::ios::failbit);
    return 0;
  }
  if (std::abs(key) > 5)
  {
    in.setstate(std::ios::failbit);
    return 0;
  }
  char tempSeparator;
  in >> std::skipws >> tempSeparator;
  if (tempSeparator != SEPARATOR)
  {
    in.setstate(std::ios::failbit);
  }

  return key;
}
std::string readStr(std::istream &in)
{
  std::string str;
  std::getline(in, str);
  if (!in)
  {
    in.setstate(std::ios::failbit);
    return "";
  }
  if (str.empty())
  {
    in.setstate(std::ios::failbit);
  }
  return str;
}

std::istream &operator>>(std::istream &in, DataStruct &dataStruct)
{
  int key1 = readKey(in);
  if (!in)
  {
    return in;
  }
  int key2 = readKey(in);
  if (!in)
  {
    return in;
  }
  std::string str = readStr(in);
  if (!in)
  {
    return in;
  }
  dataStruct = {key1, key2, str};
  return in;
}

bool operator<(const DataStruct &first, const DataStruct &second)
{
  if (first.key1 != second.key1)
  {
    return (first.key1 < second.key1);
  }
  if (first.key2 != second.key2)
  {
    return (first.key2 < second.key2);
  }
  return (first.str.length() <= second.str.length());
}

std::ostream &operator<<(std::ostream &out, const DataStruct &dataStruct)
{
  out << dataStruct.key1 << SEPARATOR << dataStruct.key2 << SEPARATOR << dataStruct.str << "\n";
  return out;
}
