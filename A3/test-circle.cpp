#include <stdexcept>

#include <boost/test/unit_test.hpp>

#include "base-types.hpp"
#include "circle.hpp"

const double EPSILON = 0.0001;
const ryzhova::point_t CENTRE = {-10.8, 4.5};
const double RADIUS = 8.4;
const double AREA = 221.6708;
const double COEFFICIENT = 5.8;

BOOST_AUTO_TEST_SUITE(circleTest)

BOOST_AUTO_TEST_CASE(incorrect_argument)
{
  BOOST_CHECK_THROW(ryzhova::Circle circle(CENTRE, -RADIUS), std::invalid_argument);
  BOOST_CHECK_THROW(ryzhova::Circle circle(CENTRE, 0), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(correct_move_dx_dy)
{
  const double dx = 3;
  const double dy = -1;
  ryzhova::Circle circle(CENTRE, RADIUS);
  circle.move(dx, dy);
  BOOST_CHECK_CLOSE(circle.getArea(), AREA, EPSILON);
  BOOST_CHECK_CLOSE(circle.getFrameRect().width, 2.0 * RADIUS, EPSILON);
  BOOST_CHECK_CLOSE(circle.getFrameRect().height, 2.0 * RADIUS, EPSILON);
  BOOST_CHECK_CLOSE(circle.getFrameRect().pos.x, CENTRE.x + dx, EPSILON);
  BOOST_CHECK_CLOSE(circle.getFrameRect().pos.y, CENTRE.y + dy, EPSILON);
}

BOOST_AUTO_TEST_CASE(correct_move_centre)
{
  const ryzhova::point_t MOVECENTRE = {8.9, -9.8};
  ryzhova::Circle circle(CENTRE, RADIUS);
  circle.move(MOVECENTRE);
  BOOST_CHECK_CLOSE(circle.getArea(), AREA, EPSILON);
  BOOST_CHECK_CLOSE(circle.getFrameRect().width, 2.0 * RADIUS, EPSILON);
  BOOST_CHECK_CLOSE(circle.getFrameRect().height, 2.0 * RADIUS, EPSILON);
  BOOST_CHECK_CLOSE(circle.getFrameRect().pos.x, MOVECENTRE.x, EPSILON);
  BOOST_CHECK_CLOSE(circle.getFrameRect().pos.y, MOVECENTRE.y, EPSILON);
}

BOOST_AUTO_TEST_CASE(correct_scale)
{
  ryzhova::Circle circle(CENTRE, RADIUS);
  circle.scale(COEFFICIENT);
  BOOST_CHECK_CLOSE(circle.getArea(), AREA * COEFFICIENT * COEFFICIENT, EPSILON);
  BOOST_CHECK_CLOSE(circle.getFrameRect().width, 2.0 * RADIUS * COEFFICIENT, EPSILON);
  BOOST_CHECK_CLOSE(circle.getFrameRect().height, 2.0 * RADIUS * COEFFICIENT, EPSILON);
  BOOST_CHECK_CLOSE(circle.getFrameRect().pos.x, CENTRE.x, EPSILON);
  BOOST_CHECK_CLOSE(circle.getFrameRect().pos.y, CENTRE.y, EPSILON);

}

BOOST_AUTO_TEST_CASE(incorrect_scale)
{
  ryzhova::Circle circle(CENTRE, RADIUS);
  BOOST_CHECK_THROW(circle.scale(-COEFFICIENT), std::invalid_argument);
  BOOST_CHECK_THROW(circle.scale(0), std::invalid_argument);

  BOOST_CHECK_CLOSE(circle.getArea(), AREA, EPSILON);
  BOOST_CHECK_EQUAL(circle.getFrameRect().width, 2.0 * RADIUS);
  BOOST_CHECK_EQUAL(circle.getFrameRect().height, 2.0 * RADIUS);
  BOOST_CHECK_EQUAL(circle.getFrameRect().pos.x, CENTRE.x);
  BOOST_CHECK_EQUAL(circle.getFrameRect().pos.y, CENTRE.y);
}

BOOST_AUTO_TEST_SUITE_END()
