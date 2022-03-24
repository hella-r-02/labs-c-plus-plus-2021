#include <stdexcept>
#include <iterator>
#include <cmath>

#include <boost/test/unit_test.hpp>

#include "shape.hpp"

const Shape triangle1 = {{{1, 0}, {5, 0}, {2, 3}}, Shape::ShapeType::TRIANGLE};
const Shape triangle2 = {{{1, 2}, {1, 2}, {1, 2}}, Shape::ShapeType::TRIANGLE};
const Shape quadrilateral = {{{2, 3}, {4, 5}, {6, 7}, {8, 9}}, Shape::ShapeType::OTHER};
const Shape square = {{{1, 2}, {2, 2}, {1, 3}, {2, 3}}, Shape::ShapeType::SQUARE};
const Shape square2 = {{{1, 2}, {1, 2}, {1, 2}, {1, 2}}, Shape::ShapeType::SQUARE};
const Shape rectangle = {{{1, 2}, {5, 2}, {1, 3}, {5, 3}}, Shape::ShapeType::RECTANGLE};
const Shape pentagon = {{{1, 3}, {1, 5}, {1, 6}, {2, 6}, {1, 4}}, Shape::ShapeType::PENTAGON};

BOOST_AUTO_TEST_SUITE(test_shape)

BOOST_AUTO_TEST_CASE(test_is_triangle)
{
  BOOST_CHECK(isTriangle(triangle1));
  BOOST_CHECK(isTriangle(triangle2));
  BOOST_CHECK(!isTriangle(quadrilateral));
}

BOOST_AUTO_TEST_CASE(test_is_rectangle)
{
  BOOST_CHECK(isRectangle(square));
  BOOST_CHECK(isRectangle(rectangle));
  BOOST_CHECK(!isRectangle(quadrilateral));
  BOOST_CHECK(!isRectangle(triangle1));
}

BOOST_AUTO_TEST_CASE(test_identical_sides)
{
  Point point1 = {1, 2};
  Point point2 = {3, 2};
  Point point3 = {1, 4};
  const double side1 = std::pow(std::pow(point1.x - point2.x, 2) + std::pow(point1.y - point2.y, 2), 0.5);
  const double side2 = std::pow(std::pow(point1.x - point3.x, 2) + std::pow(point1.y - point3.y, 2), 0.5);
  BOOST_CHECK(AreIdenticalSides(side1, side2));

  Point point4 = {2, 5};
  const double side3 = std::pow(std::pow(point1.x - point4.x, 2) + std::pow(point1.y - point4.y, 2), 0.5);
  BOOST_CHECK(!AreIdenticalSides(side1, side3));
}

BOOST_AUTO_TEST_CASE(test_is_square)
{
  BOOST_CHECK(isSquare(square));
  BOOST_CHECK(isSquare(square2));
  BOOST_CHECK(!isSquare(rectangle));
  BOOST_CHECK(!isSquare(quadrilateral));
  BOOST_CHECK(!isSquare(triangle1));
}

BOOST_AUTO_TEST_CASE(test_is_pentagon)
{
  BOOST_CHECK(isPentagon(pentagon));
  BOOST_CHECK(!isPentagon(triangle1));
}

BOOST_AUTO_TEST_CASE(test_comparator)
{
  Comparator comparator;
  std::istringstream stream;
  stream.str("5 (1;2) (2;2) (1;3) (2;3) (5;6)\n 3 (1;2) (2;3) (2;4)\n4 (2;4) (3;4) (5;4) (2;5) ");
  Shapes shapes((std::istream_iterator<Shape>(stream)), std::istream_iterator<Shape>());
  BOOST_CHECK(!comparator(pentagon, triangle2));
  BOOST_CHECK(comparator(triangle2, square));
}

BOOST_AUTO_TEST_CASE(test_correct_read_point)
{
  std::istringstream stream;
  stream.str("(1;3)");
  Point point1;
  stream >> point1;
  BOOST_CHECK(stream);
}

BOOST_AUTO_TEST_CASE(test_read_point_uncorrect_separator)
{
  std::istringstream stream2;
  stream2.str("(1,3)");
  Point point2;
  stream2 >> point2;
  BOOST_CHECK(!stream2);

  std::istringstream stream3;
  stream3.str("(1;3");
  Point point3;
  stream3 >> point3;
  BOOST_CHECK(!stream3);

  std::istringstream stream4;
  stream4.str("(1;3]");
  Point point4;
  stream4 >> point4;
  BOOST_CHECK(!stream4);

  std::istringstream stream5;
  stream5.str("1;3)");
  Point point5;
  stream5 >> point5;
  BOOST_CHECK(!stream5);

  std::istringstream stream6;
  stream6.str("[1;3)");
  Point point6;
  stream6 >> point6;
  BOOST_CHECK(!stream6);
}

BOOST_AUTO_TEST_CASE(test_correct_read_shape)
{
  Shape shape;
  std::istringstream stream;
  stream.str("3 (1;3) (2;3) (4;5)");
  stream >> shape;
  BOOST_CHECK(stream);
}

BOOST_AUTO_TEST_CASE(test_read_shape_incorrect_number_of_points)
{
  Shape shape1;
  std::istringstream stream1;
  stream1.str("3 (1;3) (2;3)");
  stream1 >> shape1;
  BOOST_CHECK(!stream1);

  Shape shape2;
  std::istringstream stream2;
  stream2.str("3 (1;3) (2;3) (5;6) (6;8)");
  stream2 >> shape2;
  BOOST_CHECK(!stream2);
}

BOOST_AUTO_TEST_CASE(test_read_shape_loss_number_of_points)
{
  Shape shape;
  std::istringstream stream;
  stream.str(" (1;3) (2;3) (5;6) (6;8)");
  stream >> shape;
  BOOST_CHECK(!stream);
}

BOOST_AUTO_TEST_CASE(test_out_point)
{
  std::ostringstream outStream;
  Point point1 = {1, 3};
  outStream << point1;
  BOOST_CHECK_EQUAL(outStream.str(), "(1;3)");
}

BOOST_AUTO_TEST_CASE(test_out_shape)
{
  std::ostringstream outStream;
  Shape shape;
  shape.points.push_back({1, 2});
  shape.points.push_back({1, 3});
  shape.points.push_back({2, 3});
  shape.type = Shape::ShapeType::TRIANGLE;
  outStream << shape;
  BOOST_CHECK_EQUAL(outStream.str(), "3 (1;2) (1;3) (2;3) ");
}

BOOST_AUTO_TEST_SUITE_END()
