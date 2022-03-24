#include <fstream>
#include <stdexcept>
#include <memory>
#include <cstring>
#include <vector>

#include "detail.hpp"

void taskTwo(const char *fileName)
{
  if (fileName == nullptr)
  {
    throw std::invalid_argument("Empty file name");
  }

  std::ifstream fin(fileName);
  if (!fin)
  {
    throw std::runtime_error("File is not found or is not open");
  }
  size_t size = 1;
  std::unique_ptr<char[], decltype(&free)> array(static_cast<char *>(malloc(size)), &free);
  if (!array)
  {
    throw std::bad_alloc();
  }
  size_t realSize = 0;
  while (fin)
  {
    fin.read(&array[realSize], size - realSize);
    realSize += fin.gcount();
    if (realSize == size)
    {
      size *= 2;
      std::unique_ptr<char[], decltype(&free)> temp(static_cast<char *>(realloc(array.get(), size)), &free);
      if (!temp)
      {
        throw std::bad_alloc();
      }
      array.release();
      array = std::move(temp);
    }
  }

  std::vector<char> vector(array.get(), array.get() + realSize);
  print(vector, "", std::cout);
}
