#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <iostream>
#include <vector>

struct Point
{
  int x, y;
};

struct Shape
{
  enum ShapeType
  {
    TRIANGLE,
    SQUARE,
    RECTANGLE,
    PENTAGON,
    OTHER
  };
  std::vector<Point> points;
  ShapeType type;
};

using Shapes = std::vector<Shape>;

std::istream &operator>>(std::istream &in, Shape &shape);
std::istream &operator>>(std::istream &in, Point &point);
std::ostream &operator<<(std::ostream &out, const Shape &shape);
std::ostream &operator<<(std::ostream &out, const Point &point);

bool isTriangle(const Shape &shape);
bool isSquare(const Shape &shape);
bool isRectangle(const Shape &shape);
bool isPentagon(const Shape &shape);
bool AreIdenticalSides(const double side1, const double side2);
double getDistanceBetweenPoints(const Point &point1, const Point &point2);

Shape::ShapeType getType(const Shape &shape);

struct Comparator
{
  bool operator()(const Shape &left, const Shape &right);
};

#endif
