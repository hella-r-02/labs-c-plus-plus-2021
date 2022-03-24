#include "rectangle.hpp"

#include <iostream>
#include <stdexcept>

Rectangle::Rectangle(const point_t &pos, double width, double height) :
  pos_(pos),
  width_(width),
  height_(height)
{
  if (width <= 0 || height <= 0)
  {
    throw std::invalid_argument("not positive parameters");
  }
}

double Rectangle::getArea() const
{
  return width_ * height_;
}

rectangle_t Rectangle::getFrameRect() const
{
  return {width_, height_, pos_};
}

void Rectangle::move(double dx,double dy)
{
  pos_.x += dx;
  pos_.y += dy;
}

void Rectangle::move(const point_t &centre)
{
  pos_ = centre;
}

void Rectangle::print() const
{
  const rectangle_t temp = getFrameRect();
  std::cout << "Height and width of the rectangle: height = " << temp.height << ", width = " << temp.width
            << "\nCoordinates of the center of the rectangle: x = " << temp.pos.x << ", y = " << temp.pos.y
            << "\nSquare: " << getArea() << "\n";
}

