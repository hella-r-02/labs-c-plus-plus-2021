#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <iterator>

#include "data-struct.hpp"

void task(std::istream &in, std::ostream &out);

int main()
{
  try
  {
    task(std::cin, std::cout);
  }
  catch (const std::runtime_error &error)
  {
    std::cerr << error.what();
    return 2;
  }
  catch (const std::exception &error)
  {
    std::cerr << error.what();
    return 2;
  }
  return 0;
}

void task(std::istream &in, std::ostream &out)
{
  std::vector<DataStruct> vector((std::istream_iterator<DataStruct>(in)), std::istream_iterator<DataStruct>());
  if (!in.eof())
  {
    throw std::runtime_error("an error occurred while reading");
  }

  std::sort(vector.begin(), vector.end(), Comparator());
  std::copy(vector.begin(), vector.end(), std::ostream_iterator<DataStruct>(out));
}
