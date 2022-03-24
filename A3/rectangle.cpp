#include "rectangle.hpp"

#include <stdexcept>

ryzhova::Rectangle::Rectangle(const point_t &pos, double width, double height) :
  pos_(pos),
  width_(width),
  height_(height)
{
  if ((width <= 0) || (height <= 0))
  {
    throw std::invalid_argument("not positive parameters");
  }
}

double ryzhova::Rectangle::getArea() const
{
  return width_ * height_;
}

ryzhova::rectangle_t ryzhova::Rectangle::getFrameRect() const
{
  return {width_, height_, pos_};
}

void ryzhova::Rectangle::move(double dx, double dy)
{
  pos_.x += dx;
  pos_.y += dy;
}

void ryzhova::Rectangle::move(const point_t &centre)
{
  pos_ = centre;
}

void ryzhova::Rectangle::print(std::ostream &out) const
{
  const rectangle_t temp = getFrameRect();
  out << "Height and width of the rectangle: height = " << temp.height << ", width = " << temp.width
      << "\nCoordinates of the center of the rectangle: x = " << temp.pos.x << ", y = " << temp.pos.y
      << "\nSquare: " << getArea() << "\n";
}
void ryzhova::Rectangle::scale(double coefficient)
{
  if (coefficient <= 0)
  {
    throw std::invalid_argument("not positive coefficient");
  }

  width_ *= coefficient;
  height_ *= coefficient;
}
