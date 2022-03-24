#include "circle.hpp"

#include <cmath>
#include <stdexcept>

ryzhova::Circle::Circle(const point_t &pos, double radius) :
  pos_(pos),
  radius_(radius)
{
  if (radius <= 0)
  {
    throw std::invalid_argument("not positive parameters");
  }
}

double ryzhova::Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

ryzhova::rectangle_t ryzhova::Circle::getFrameRect() const
{
  return {radius_ * 2, radius_ * 2, pos_};
}

void ryzhova::Circle::move(double dx, double dy)
{
  pos_.x += dx;
  pos_.y += dy;
}

void ryzhova::Circle::move(const point_t &centre)
{
  pos_ = centre;
}

void ryzhova::Circle::print(std::ostream &out) const
{
  const rectangle_t temp = getFrameRect();
  out << "Border rectangle: height = " << temp.height << ", width = " << temp.width << "\n"
      << "Coordinates of the center of the circle: x = " << pos_.x << ", y = " << pos_.y << "\n"
      << "Square: " << getArea() << "\n";
}
void ryzhova::Circle::scale(double coefficient)
{
  if (coefficient <= 0)
  {
    throw std::invalid_argument("not positive coefficient");
  }
  radius_ *= coefficient;
}
