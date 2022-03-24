#include <iostream>
#include <sstream>
#include <stdexcept>

#include "tasks.hpp"

int main(int argc, char *argv[])
{
  try
  {
    if (argc != 2)
    {
      std::cerr << "Incorrect count of elements";
      return 2;
    }
    int task = 0;
    std::istringstream stream(argv[1]);
    stream >> task;
    if (!stream.eof())
    {
      std::cerr << "Wrong task number";
      return 2;
    }
    if ((task != 1) && (task != 2))
    {
      std::cerr << "Wrong task number";
      return 2;
    }
    if (task == 1)
    {
      try
      {
        task1(std::cin, std::cout);
      }
      catch (const std::runtime_error &error)
      {
        std::cerr << error.what();
        return 1;
      }
    }
    else if (task == 2)
    {
      try
      {
        task2(std::cout);
      }
      catch (const std::out_of_range &error)
      {
        std::cerr << error.what();
        return 1;
      }
    }
  }
  catch (const std::exception &error)
  {
    std::cerr << error.what() << "\n";
    return 3;
  }
  return 0;
}
