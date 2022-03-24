#include "circle.hpp"

#include <cmath>
#include <iostream>
#include <stdexcept>

Circle::Circle(const point_t &pos, double radius) :
  pos_(pos),
  radius_(radius)
{
  if (radius <= 0)
  {
    throw std::invalid_argument("not positive parameters");
  }
}

double Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

rectangle_t Circle::getFrameRect() const
{
  return {radius_ * 2,radius_ * 2, pos_ };
}

void Circle::move(double dx, double dy)
{
  pos_.x += dx;
  pos_.y += dy;
}

void Circle::move(const point_t &centre)
{
  pos_ = centre;
}

void Circle::print() const
{
  const rectangle_t temp = getFrameRect();
  std::cout << "Border rectangle: height = " << temp.height << ", width = " << temp.width << "\n"
            << "Coordinates of the center of the circle: x = " << pos_.x << ", y = " << pos_.y << "\n"
            << "Square: " << getArea() << "\n";
}
