#ifndef TASK_HPP
#define TASK_HPP

#include <iostream>

struct DataStruct
{
  int key1;
  int key2;
  std::string str;
};

std::istream &operator>>(std::istream &in, DataStruct &dataStruct);
std::ostream &operator<<(std::ostream &out, const DataStruct &dataStruct);

struct Comparator
{
  bool operator()(const DataStruct& left, const DataStruct& right);
};

#endif
