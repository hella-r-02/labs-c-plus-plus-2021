#include <stdexcept>

#include <boost/test/unit_test.hpp>

#include "rectangle.hpp"
#include "base-types.hpp"

BOOST_AUTO_TEST_SUITE(rectangleTest)
const double EPSILON = 0.0001;
const ryzhova::point_t CENTRE = {-1.3, 4.9};
const double WIDTH = 2.3;
const double HEIGHT = 3.5;
const double AREA = 8.05;
const double COEFFICIENT = 0.5;
BOOST_AUTO_TEST_CASE(incorrect_argument)
{
  BOOST_CHECK_THROW(ryzhova::Rectangle rectangle(CENTRE, -WIDTH, HEIGHT), std::invalid_argument);
  BOOST_CHECK_THROW(ryzhova::Rectangle rectangle(CENTRE, WIDTH, -HEIGHT), std::invalid_argument);
  BOOST_CHECK_THROW(ryzhova::Rectangle rectangle(CENTRE, -WIDTH, -HEIGHT), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(correct_move_dx_dy)
{
  const double dx = 1.2;
  const double dy = -20.3;
  ryzhova::Rectangle rectangle(CENTRE, WIDTH, HEIGHT);
  rectangle.move(dx, dy);
  BOOST_CHECK_CLOSE(rectangle.getArea(), AREA, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, WIDTH, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, HEIGHT, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.x, CENTRE.x + dx, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.y, CENTRE.y + dy, EPSILON);
}

BOOST_AUTO_TEST_CASE(correct_move_centre)
{
  const ryzhova::point_t MOVECENTRE = {-12.3, 4.8};
  ryzhova::Rectangle rectangle(CENTRE, WIDTH, HEIGHT);
  rectangle.move(MOVECENTRE);
  BOOST_CHECK_CLOSE(rectangle.getArea(), AREA, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, WIDTH, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, HEIGHT, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.x, MOVECENTRE.x, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.y, MOVECENTRE.y, EPSILON);
}

BOOST_AUTO_TEST_CASE(correct_scale_coefficient_greater_than_zero)
{
  ryzhova::Rectangle rectangle(CENTRE, WIDTH, HEIGHT);
  rectangle.scale(COEFFICIENT);
  BOOST_CHECK_CLOSE(rectangle.getArea(), AREA * COEFFICIENT * COEFFICIENT, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, WIDTH * COEFFICIENT, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, HEIGHT * COEFFICIENT, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.x, CENTRE.x, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.y, CENTRE.y, EPSILON);

}

BOOST_AUTO_TEST_CASE(incorrect_scale)
{
  ryzhova::Rectangle rectangle(CENTRE, WIDTH, HEIGHT);
  BOOST_CHECK_THROW(rectangle.scale(-COEFFICIENT), std::invalid_argument);
  BOOST_CHECK_THROW(rectangle.scale(0), std::invalid_argument);

  BOOST_CHECK_CLOSE(rectangle.getArea(), AREA, EPSILON);
  BOOST_CHECK_EQUAL(rectangle.getFrameRect().width, WIDTH);
  BOOST_CHECK_EQUAL(rectangle.getFrameRect().height, HEIGHT);
  BOOST_CHECK_EQUAL(rectangle.getFrameRect().pos.x, CENTRE.x);
  BOOST_CHECK_EQUAL(rectangle.getFrameRect().pos.y, CENTRE.y);
}

BOOST_AUTO_TEST_SUITE_END()
