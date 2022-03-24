#include <iostream>
#include <stdexcept>
#include <sstream>
#include <unordered_set>
#include <iterator>
#include <algorithm>

#include "shape.hpp"

void task1(std::istream &in, std::ostream &out);
void task2(std::istream &in, std::ostream &out);

int main(int argc, char *argv[])
{
  try
  {
    if (argc != 2)
    {
      std::cerr << "invalid arguments" << "\n";
      return 1;
    }

    std::istringstream stream(argv[1]);
    int taskNumber;
    stream >> taskNumber;
    if (!stream.eof())
    {
      std::cerr << "invalid task number";
      return 1;
    }
    if (taskNumber == 1)
    {
      try
      {
        task1(std::cin, std::cout);
      }
      catch (const std::runtime_error &error)
      {
        std::cerr << error.what();
        return 2;
      }
    }
    else if (taskNumber == 2)
    {
      try
      {
        task2(std::cin, std::cout);
      }
      catch (const std::runtime_error &error)
      {
        std::cerr << error.what();
        return 2;
      }
    }
    else
    {
      std::cerr << "Wrong task number";
      return 2;
    }
  }
  catch (const std::exception &exception)
  {
    std::cerr << exception.what();
    return 3;
  }
  return 0;
}

void task1(std::istream &in, std::ostream &out)
{
  std::istream_iterator<std::string> inputIterator(in);
  std::istream_iterator<std::string> endIterator;
  std::unordered_set<std::string> setString(inputIterator, endIterator);
  if (!in.eof())
  {
    std::runtime_error("error in reading words");
  }
  std::copy(setString.begin(), setString.end(), std::ostream_iterator<std::string>(out, "\n"));
}

void task2(std::istream &in, std::ostream &out)
{
  Shapes shapes((std::istream_iterator<Shape>(in)), std::istream_iterator<Shape>());
  if (!in.eof())
  {
    throw std::runtime_error("error in reading shapes");
  }

  size_t numberOfVertices = 0;
  std::for_each(shapes.begin(), shapes.end(),
      [&numberOfVertices](const Shape &shape)
      {
        numberOfVertices += shape.points.size();
      });

  size_t numberOfTriangles = std::count_if(shapes.begin(), shapes.end(),
      [&](const Shape &shape)
      {
        return shape.type == Shape::TRIANGLE;
      });
  size_t numberOfSquares = std::count_if(shapes.begin(), shapes.end(),
      [&](const Shape &shape)
      {
        return shape.type == Shape::SQUARE;
      });
  size_t numberOfRectangles = std::count_if(shapes.begin(), shapes.end(),
      [&](const Shape &shape)
      {
       return shape.type == Shape::RECTANGLE;
      });
  numberOfRectangles += numberOfSquares;

  shapes.erase(std::remove_if(shapes.begin(), shapes.end(),
      [&](Shape &shape)
      {
        return shape.type == Shape::PENTAGON;
      }),
      shapes.end());

  std::vector<Point> points(shapes.size());
  std::transform(shapes.begin(), shapes.end(), points.begin(),
      [&](const Shape &shape)
      {
        return shape.points[0];
      });

  std::sort(shapes.begin(), shapes.end(), Comparator());

  out << "Vertices: " << numberOfVertices << "\nTriangles: " << numberOfTriangles << "\nSquares: " << numberOfSquares
      << "\nRectangles: " << numberOfRectangles << "\nPoints: ";
  std::copy(points.begin(), points.end(), std::ostream_iterator<Point>(out, " "));
  out << "\nShapes:\n";
  std::copy(shapes.begin(), shapes.end(), std::ostream_iterator<Shape>(out, "\n"));
}
