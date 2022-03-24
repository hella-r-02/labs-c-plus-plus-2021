#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"
#include "base-types.hpp"

class Rectangle: public Shape
{
public:
  Rectangle(const point_t &pos, double width, double height);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(double x, double y) override;
  void move(const point_t &centre) override;
  void print() const override;

private:
  point_t pos_;
  double width_, height_;
};

#endif
