#include <memory>
#include <stdexcept>

#include <boost/test/unit_test.hpp>

#include "base-types.hpp"
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

const ryzhova::point_t centreRectangle = {2.4, 3.5};
const ryzhova::point_t centreCircle = {1.3, 4.9};
const double WIDTH = 2.3;
const double HEIGHT = 3.5;
const double RADIUS = 2.5;
const double EPSILON = 0.0001;
const ryzhova::point_t MOVECENTRE = {3.4, 5.3};
const double COEFFICIENT = 1.5;
const double dx = 3.4;
const double dy = 9.3;

BOOST_AUTO_TEST_SUITE(compositeShapeTest)
struct fixture
{
  ryzhova::Shape::Ptr circle;
  ryzhova::Shape::Ptr rectangle;
  ryzhova::CompositeShape compositeShape;

  fixture() :
    circle(std::make_shared<ryzhova::Circle>(ryzhova::Circle(centreCircle, RADIUS))),
    rectangle(std::make_shared<ryzhova::Rectangle>(ryzhova::Rectangle({centreRectangle, WIDTH, HEIGHT})))
  {
    compositeShape.addShape(rectangle);
    compositeShape.addShape(circle);
  }
};

BOOST_AUTO_TEST_CASE(empty_composite_shape)
{
  ryzhova::CompositeShape emptyCompositeShape;
  BOOST_CHECK_CLOSE(emptyCompositeShape.getArea(), 0, EPSILON);
  BOOST_CHECK_THROW(emptyCompositeShape.getFrameRect(), std::length_error);
  BOOST_CHECK_THROW(emptyCompositeShape.move(dx, dy), std::length_error);
  BOOST_CHECK_THROW(emptyCompositeShape.move(MOVECENTRE), std::length_error);
  BOOST_CHECK_THROW(emptyCompositeShape.scale(COEFFICIENT), std::length_error);
  BOOST_CHECK_THROW(emptyCompositeShape[0],std::out_of_range);
}

BOOST_FIXTURE_TEST_CASE(invalid_argument_add_shape,fixture)
{
  BOOST_CHECK_THROW(compositeShape.addShape(nullptr), std::invalid_argument);
  BOOST_CHECK_THROW(compositeShape.addShape(circle), std::invalid_argument);
  std::shared_ptr<ryzhova::CompositeShape> compositeShape2 = std::make_shared<ryzhova::CompositeShape>();
  BOOST_CHECK_THROW(compositeShape2->addShape(compositeShape2), std::logic_error);
}

BOOST_FIXTURE_TEST_CASE(invalid_argument_delete_shape,fixture)
{
  BOOST_CHECK_THROW(compositeShape.deleteShape(2),std::out_of_range);

  ryzhova::CompositeShape emptyCompositeShape;
  BOOST_CHECK_THROW(emptyCompositeShape.deleteShape(1),std::length_error);
}
BOOST_FIXTURE_TEST_CASE(delete_shape,fixture)
{
  BOOST_CHECK_EQUAL(compositeShape.getSize(), 2);
  const double compositeShapeArea = compositeShape.getArea();
  const double deleteArea = compositeShape[1]->getArea();
  compositeShape.deleteShape(1);
  BOOST_CHECK_EQUAL(compositeShape.getSize(), 1);
  BOOST_CHECK_CLOSE(compositeShape.getArea(), compositeShapeArea - deleteArea, EPSILON);
}
BOOST_FIXTURE_TEST_CASE(copy_constructor, fixture)
{
  size_t size = compositeShape.getSize();
  ryzhova::CompositeShape copyCompositeShape(compositeShape);
  BOOST_CHECK_EQUAL(copyCompositeShape.getSize(), compositeShape.getSize());
  BOOST_CHECK_EQUAL(compositeShape.getSize(), size);
  BOOST_CHECK_EQUAL(copyCompositeShape[0], compositeShape[0]);
  BOOST_CHECK_EQUAL(copyCompositeShape[1], compositeShape[1]);

  ryzhova::CompositeShape compositeShapeNull;
  ryzhova::CompositeShape copyCompositeShape2(compositeShape);
  BOOST_CHECK_EQUAL(copyCompositeShape2.getSize(), compositeShape.getSize());
}

BOOST_FIXTURE_TEST_CASE(copy_assignment_operator, fixture)
{
  size_t size = compositeShape.getSize();
  ryzhova::CompositeShape copyCompositeShape = compositeShape;
  BOOST_CHECK_EQUAL(copyCompositeShape.getSize(), compositeShape.getSize());
  BOOST_CHECK_EQUAL(compositeShape.getSize(), size);
  BOOST_CHECK_EQUAL(copyCompositeShape[0], compositeShape[0]);
  BOOST_CHECK_EQUAL(copyCompositeShape[1], compositeShape[1]);

  ryzhova::CompositeShape compositeShapeNull;
  ryzhova::CompositeShape copyCompositeShape2(compositeShapeNull);
  BOOST_CHECK_EQUAL(copyCompositeShape2.getSize(), 0);
}

BOOST_FIXTURE_TEST_CASE(move_constructor, fixture)
{
  size_t size = compositeShape.getSize();
  ryzhova::CompositeShape moveCompositeShape(std::move(compositeShape));
  BOOST_CHECK_EQUAL(moveCompositeShape.getSize(), size);
  BOOST_CHECK_EQUAL(compositeShape.getSize(), 0);
  BOOST_CHECK_EQUAL(moveCompositeShape[0], rectangle);
  BOOST_CHECK_EQUAL(moveCompositeShape[1], circle);

  ryzhova::CompositeShape compositeShapeNull;
  ryzhova::CompositeShape moveCompositeShape2(std::move(compositeShapeNull));
  BOOST_CHECK_EQUAL(moveCompositeShape2.getSize(), 0);
}

BOOST_FIXTURE_TEST_CASE(move_assignment_operator, fixture)
{
  size_t size = compositeShape.getSize();
  ryzhova::CompositeShape moveCompositeShape = std::move(compositeShape);
  BOOST_CHECK_EQUAL(moveCompositeShape.getSize(), size);
  BOOST_CHECK_EQUAL(compositeShape.getSize(), 0);
  BOOST_CHECK_EQUAL(moveCompositeShape[0], rectangle);
  BOOST_CHECK_EQUAL(moveCompositeShape[1], circle);

  ryzhova::CompositeShape compositeShapeNull;
  ryzhova::CompositeShape moveCompositeShape2 = std::move(compositeShapeNull);
  BOOST_CHECK_EQUAL(moveCompositeShape2.getSize(), 0);

}

BOOST_FIXTURE_TEST_CASE(correct_move_dx_dy, fixture)
{
  const ryzhova::rectangle_t rectangleCompositeShape = compositeShape.getFrameRect();
  const double areaCompositeShape = compositeShape.getArea();
  compositeShape.move(dx, dy);
  BOOST_CHECK_CLOSE(compositeShape.getArea(), areaCompositeShape, EPSILON);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().width, rectangleCompositeShape.width, EPSILON);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().height, rectangleCompositeShape.height, EPSILON);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().pos.x, rectangleCompositeShape.pos.x + dx, EPSILON);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().pos.y, rectangleCompositeShape.pos.y + dy, EPSILON);
}

BOOST_FIXTURE_TEST_CASE(correct_move_centre, fixture)
{
  const ryzhova::rectangle_t rectangleCompositeShape = compositeShape.getFrameRect();
  const double areaCompositeShape = compositeShape.getArea();
  compositeShape.move(MOVECENTRE);
  BOOST_CHECK_CLOSE(compositeShape.getArea(), areaCompositeShape, EPSILON);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().width, rectangleCompositeShape.width, EPSILON);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().height, rectangleCompositeShape.height, EPSILON);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().pos.x, MOVECENTRE.x, EPSILON);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().pos.y, MOVECENTRE.y, EPSILON);
}

BOOST_FIXTURE_TEST_CASE(correct_scale, fixture)
{
  const ryzhova::rectangle_t rectangleCompositeShape = compositeShape.getFrameRect();
  const double areaCompositeShape = compositeShape.getArea();
  const double rectanglePosDx = (rectangle->getFrameRect().pos.x - rectangleCompositeShape.pos.x) * COEFFICIENT;
  const double rectanglePosDy = (rectangle->getFrameRect().pos.y - rectangleCompositeShape.pos.y) * COEFFICIENT;
  const double circlePosDx = (circle->getFrameRect().pos.x - rectangleCompositeShape.pos.x) * COEFFICIENT;
  const double circlePosDy = (circle->getFrameRect().pos.y - rectangleCompositeShape.pos.y) * COEFFICIENT;
  compositeShape.scale(COEFFICIENT);
  BOOST_CHECK_CLOSE(compositeShape.getArea(), areaCompositeShape * COEFFICIENT * COEFFICIENT, EPSILON);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().width, rectangleCompositeShape.width * COEFFICIENT, EPSILON);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().height, rectangleCompositeShape.height * COEFFICIENT, EPSILON);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().pos.x, rectangleCompositeShape.pos.x, EPSILON);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().pos.y, rectangleCompositeShape.pos.y, EPSILON);

  BOOST_CHECK_CLOSE(compositeShape[0]->getFrameRect().pos.x, rectangleCompositeShape.pos.x + rectanglePosDx, EPSILON);
  BOOST_CHECK_CLOSE(compositeShape[0]->getFrameRect().pos.y, rectangleCompositeShape.pos.y + rectanglePosDy, EPSILON);
  BOOST_CHECK_CLOSE(compositeShape[1]->getFrameRect().pos.x, rectangleCompositeShape.pos.x + circlePosDx, EPSILON);
  BOOST_CHECK_CLOSE(compositeShape[1]->getFrameRect().pos.y, rectangleCompositeShape.pos.y + circlePosDy, EPSILON);
}

BOOST_FIXTURE_TEST_CASE(incorrect_scale, fixture)
{
  BOOST_CHECK_THROW(compositeShape.scale(-COEFFICIENT), std::invalid_argument);
  BOOST_CHECK_THROW(compositeShape.scale(0), std::invalid_argument);

  const ryzhova::rectangle_t rectangleCompositeShape = compositeShape.getFrameRect();
  const double areaCompositeShape = compositeShape.getArea();

  BOOST_CHECK_EQUAL(compositeShape.getArea(), areaCompositeShape);
  BOOST_CHECK_EQUAL(compositeShape.getFrameRect().width, rectangleCompositeShape.width);
  BOOST_CHECK_EQUAL(compositeShape.getFrameRect().height, rectangleCompositeShape.height);
  BOOST_CHECK_EQUAL(compositeShape.getFrameRect().pos.x, rectangleCompositeShape.pos.x);
  BOOST_CHECK_EQUAL(compositeShape.getFrameRect().pos.y, rectangleCompositeShape.pos.y);
  BOOST_CHECK_EQUAL(compositeShape[0]->getFrameRect().pos.x, centreRectangle.x);
  BOOST_CHECK_EQUAL(compositeShape[0]->getFrameRect().pos.y, centreRectangle.y);
  BOOST_CHECK_EQUAL(compositeShape[1]->getFrameRect().pos.x, centreCircle.x);
  BOOST_CHECK_EQUAL(compositeShape[1]->getFrameRect().pos.y, centreCircle.y);
  BOOST_CHECK_EQUAL(compositeShape[0]->getArea(), rectangle->getArea());
  BOOST_CHECK_EQUAL(compositeShape[1]->getArea(), circle->getArea());
}

BOOST_AUTO_TEST_SUITE_END()
