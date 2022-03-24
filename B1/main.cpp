#include <iostream>
#include <stdexcept>
#include <sstream>
#include <functional>

#include "tasks.hpp"
#include "sort.hpp"

int main(int argc, char *argv[])
{
  try
  {
    if (argc < 2 || argc > 4)
    {
      std::cerr << "Incorrect count of elements";
      return 1;
    }
    if(strlen(argv[1])!=1)
    {
      std::cerr << "Wrong task number";
      return 1;
    }
    std::istringstream taskNumberStream(argv[1]);
    size_t task = 0;
    taskNumberStream >> task;
    if (taskNumberStream.fail())
    {
      std::cerr << "Wrong task number";
      return 1;
    }
    if (task == 1)
    {
      if (argc != 3)
      {
        std::cerr << "Incorrect count of elements";
        return 1;
      }
      try
      {
        std::function<bool(const int&, const int&)>  comparator = determineOrder<int>(argv[2]);
        taskOne(comparator);
      }
      catch (const std::invalid_argument &error)
      {
        std::cerr << error.what();
        return 3;
      }
    }
    else if (task == 2)
    {
      if (argc != 3)
      {
        std::cerr << "Incorrect count of elements";
        return 1;
      }
      try
      {
        taskTwo(argv[2]);
      }
      catch (const std::invalid_argument &error)
      {
        std::cerr << error.what();
        return 3;
      }
      catch (const std::bad_alloc &error)
      {
        std::cerr << error.what();
        return 3;
      }
    }
    else if (task == 3)
    {
      if (argc != 2)
      {
        std::cerr << "Incorrect count of elements";
        return 1;
      }
      try
      {
        taskThree();
      }
      catch (const std::invalid_argument &error)
      {
        std::cerr << error.what();
        return 3;
      }
    }
    else if (task == 4)
    {
      if (argc != 4)
      {
        std::cerr << "Incorrect count of elements";
        return 1;
      } else
      {
        try
        {
          std::istringstream sizeArrayStream(argv[3]);
          size_t size = 0;
          sizeArrayStream >> size;
          if (!sizeArrayStream.eof())
          {
            std::cerr << "Wrong size";
            return 1;
          }
          auto comparator = determineOrder<double>(argv[2]);
          taskFour(comparator, size);
        }
        catch (const std::invalid_argument &error)
        {
          std::cerr << error.what();
          return 3;
        }
      }
    }
    else
    {
      std::cerr << "Invalid task number";
      return 1;
    }
  }

  catch (const std::exception &exception)
  {
    std::cerr << exception.what();
    return 2;
  }
  return 0;
}
