#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include <memory>

#include "shape.hpp"

namespace ryzhova
{
  class CompositeShape
    : public Shape
  {
  public:
    CompositeShape();
    CompositeShape(const CompositeShape &srcCompositeShape);
    CompositeShape(CompositeShape &&srcCompositeShape) noexcept;
    ~CompositeShape() = default;
    CompositeShape &operator=(const CompositeShape &srcCompositeShape);
    CompositeShape &operator=(CompositeShape &&srcCompositeShape) noexcept;
    void addShape(const std::shared_ptr<Shape> &new_shape);
    void deleteShape(size_t index);
    std::shared_ptr<Shape> operator[](size_t index) const;
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(double dx, double dy) override;
    void move(const point_t &centre) override;
    void scale(double coefficient) override;
    void print(std::ostream &out) const override;
    size_t getSize() const;

  private:
    using ShapeArray = std::unique_ptr<Ptr[]>;
    size_t size_;
    ShapeArray shapeArray_;
  };
}
#endif
