#ifndef SHAPE_HPP
#define SHAPE_HPP

struct  point_t;
struct rectangle_t;

class Shape
{
public:
  virtual ~Shape() = default;
  virtual double getArea() const = 0;
  virtual rectangle_t getFrameRect() const = 0;
  virtual void move(double dx, double dy) = 0;
  virtual void move(const point_t &centre) = 0;
  virtual void print() const = 0;
};

#endif

