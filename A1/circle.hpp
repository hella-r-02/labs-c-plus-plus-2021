#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"
#include "base-types.hpp"

class Circle : public Shape {
public:
  Circle(const point_t &pos, double radius);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(double dx, double dy) override;
  void move(const point_t &centre) override;
  void print() const override;

private:
  point_t pos_;
  double radius_;
};

#endif
