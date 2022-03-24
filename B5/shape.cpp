#include "shape.hpp"

#include <algorithm>
#include <iterator>
#include <cmath>

#include "utility.hpp"

namespace detail
{
const char openingParenthesis = '(';
const char closingParenthesis = ')';
const char semicolon = ';';
const char sss='s';

const double epsilon = 0.00000001;
const size_t triangleSize = 3;
const size_t rectangleSize = 4;
const size_t pentagonSize = 5;
}

std::istream &operator>>(std::istream &in, Shape &shape)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  StreamGuard stream(in);
  size_t numberOfVertexes;
  in >> std::noskipws >> std::ws >> numberOfVertexes;
  if (!in)
  {
    return in;
  }
  if (numberOfVertexes == 0)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  std::vector<Point> tempShape;
  for (size_t i = 0; i < numberOfVertexes; i++)
  {
    Point point;
    in >> point;
    if (!in)
    {
      return in;
    }
    tempShape.push_back(point);
  }
  in >> skip_ws;
  if (in.eof() || (in.peek() == '\n') || (in.peek() == '\r'))
  {
    shape.points = std::move(tempShape);
  }
  else
  {
    in.setstate(std::ios::failbit);
  }
  shape.type = getType(shape);
  return in;
}

std::istream &operator>>(std::istream &in, Point &point)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  StreamGuard stream(in);
  in >> std::noskipws;

  Separator separator1(detail::openingParenthesis);
  int x, y;
  Separator separator2(detail::semicolon);
  Separator separator3(detail::closingParenthesis);
  if (!(in >> skip_ws >> separator1 >> skip_ws >> x >> skip_ws >> separator2 >> skip_ws >> y >> skip_ws >> separator3))
  {
    return in;
  }
  point = {x, y};

  return in;
}

bool isTriangle(const Shape &shape)
{
  return shape.points.size() == detail::triangleSize;
}

bool isRectangle(const Shape &shape)
{
  if (shape.points.size() != detail::rectangleSize)
  {
    return false;
  }
  const double lengthAB = getDistanceBetweenPoints(shape.points[0], shape.points[1]);
  const double lengthDC = getDistanceBetweenPoints(shape.points[2], shape.points[3]);
  if (AreIdenticalSides(lengthAB, lengthDC))
  {
    const double lengthAD = getDistanceBetweenPoints(shape.points[0], shape.points[3]);
    const double lengthBC = getDistanceBetweenPoints(shape.points[1], shape.points[2]);
    const double lengthAC = getDistanceBetweenPoints(shape.points[2], shape.points[0]);
    const double BD = getDistanceBetweenPoints(shape.points[3], shape.points[1]);
    return (AreIdenticalSides(lengthAD, lengthBC)) && (AreIdenticalSides(lengthAC, BD));
  }
  else
  {
    const double lengthCA = getDistanceBetweenPoints(shape.points[1], shape.points[0]);
    const double lengthBD = getDistanceBetweenPoints(shape.points[3], shape.points[2]);
    const double lengthBA = getDistanceBetweenPoints(shape.points[2], shape.points[0]);
    const double lengthCD = getDistanceBetweenPoints(shape.points[3], shape.points[1]);
    const double lengthAD = getDistanceBetweenPoints(shape.points[3], shape.points[0]);
    const double lengthBC = getDistanceBetweenPoints(shape.points[1], shape.points[2]);
    return (AreIdenticalSides(lengthCA, lengthBD)) && (AreIdenticalSides(lengthBA, lengthCD))
      && (AreIdenticalSides(lengthAD, lengthBC));
  }
}

bool isSquare(const Shape &shape)
{
  if (!isRectangle(shape))
  {
    return false;
  }
  const double side1 = getDistanceBetweenPoints(shape.points[0], shape.points[1]);
  const double side2 = getDistanceBetweenPoints(shape.points[0], shape.points[2]);
  if (AreIdenticalSides(side1, side2))
  {
    return true;
  }
  const double side3 = getDistanceBetweenPoints(shape.points[0], shape.points[3]);
  return AreIdenticalSides(side1, side3);
}

bool isPentagon(const Shape &shape)
{
  return shape.points.size() == detail::pentagonSize;
}

std::ostream &operator<<(std::ostream &out, const Shape &shape)
{
  std::ostream::sentry sentry(out);
  if (sentry)
  {
    out << shape.points.size() << " ";
    std::copy(shape.points.begin(), shape.points.end(), std::ostream_iterator<Point>(out, " "));
  }
  return out;
}

std::ostream &operator<<(std::ostream &out, const Point &point)
{
  std::ostream::sentry sentry(out);
  if (sentry)
  {
    out << detail::openingParenthesis << point.x << detail::semicolon << point.y << detail::closingParenthesis;
  }
  return out;
}

Shape::ShapeType getType(const Shape &shape)
{
  if (isTriangle(shape))
  {
    return Shape::TRIANGLE;
  }
  else if (isSquare(shape))
  {
    return Shape::SQUARE;
  }
  else if (isRectangle(shape))
  {
    return Shape::RECTANGLE;
  }
  else if (isPentagon(shape))
  {
    return Shape::PENTAGON;
  }
  return Shape::OTHER;
}

double getDistanceBetweenPoints(const Point &point1, const Point &point2)
{
  return std::pow((std::pow(point1.x - point2.x, 2) + std::pow(point1.y - point2.y, 2)), 0.5);
}

inline bool AreIdenticalSides(const double side1, const double side2)
{
  return std::fabs(side2 - side1) < detail::epsilon;
}

bool Comparator::operator()(const Shape &left, const Shape &right)
{
  return left.type < right.type;
}
