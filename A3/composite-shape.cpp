#include "composite-shape.hpp"

#include <stdexcept>

#include "base-types.hpp"

ryzhova::CompositeShape::CompositeShape() :
  size_(0)
{}

ryzhova::CompositeShape::CompositeShape(const ryzhova::CompositeShape &srcCompositeShape) :
  size_(srcCompositeShape.size_)
{
  if (srcCompositeShape.size_)
  {
    shapeArray_ = std::make_unique<Ptr[]>(srcCompositeShape.size_);
    for (size_t i = 0; i < srcCompositeShape.size_; i++)
    {
      shapeArray_[i] = srcCompositeShape.shapeArray_[i];
    }
    size_ = srcCompositeShape.size_;
  }
}

ryzhova::CompositeShape::CompositeShape(CompositeShape &&srcCompositeShape) noexcept:
  size_(srcCompositeShape.size_),
  shapeArray_(std::move(srcCompositeShape.shapeArray_))
{
  srcCompositeShape.size_ = 0;
}

ryzhova::CompositeShape &ryzhova::CompositeShape::operator=(const ryzhova::CompositeShape &srcCompositeShape)
{
  if (this == &srcCompositeShape)
  {
    return *this;
  }
  if (srcCompositeShape.size_ != 0)
  {
    shapeArray_ = std::make_unique<Ptr[]>(srcCompositeShape.size_);
  }
  size_ = srcCompositeShape.size_;
  for (size_t i = 0; i < srcCompositeShape.size_; i++)
  {
    shapeArray_[i] = srcCompositeShape.shapeArray_[i];
  }
  return *this;
}

ryzhova::CompositeShape &ryzhova::CompositeShape::operator=(ryzhova::CompositeShape &&srcCompositeShape) noexcept
{
  if (this == &srcCompositeShape)
  {
    return *this;
  }
  size_ = srcCompositeShape.size_;
  shapeArray_ = std::move(srcCompositeShape.shapeArray_);
  srcCompositeShape.size_ = 0;
  return *this;
}

void ryzhova::CompositeShape::addShape(const std::shared_ptr<Shape> &newShape)
{
  if ((newShape == nullptr) || (newShape.get() == this))
  {
    throw std::invalid_argument("new shape is not correct");
  }
  std::unique_ptr<Shape::Ptr[]> tempArray = std::make_unique<Shape::Ptr[]>(size_ + 1);
  for (size_t i = 0; i < size_; i++)
  {
    if (shapeArray_[i].get() == newShape.get())
    {
      throw std::invalid_argument("this shape already exists in composite shape");
    }
    tempArray[i] = shapeArray_[i];
  }
  shapeArray_ = std::move(tempArray);
  shapeArray_[size_] = newShape;
  size_++;
}

void ryzhova::CompositeShape::deleteShape(size_t index)
{
  if (size_ == 0)
  {
    throw std::length_error("shape is empty");
  }
  if (index >= size_)
  {
    throw std::out_of_range("wrong index");
  }
  for (size_t i = index; i < size_-1; i++)
  {
    shapeArray_[i] = shapeArray_[i + 1];
  }
  shapeArray_[--size_].reset();
}

std::shared_ptr<ryzhova::Shape> ryzhova::CompositeShape::operator[](std::size_t index) const
{
  if (index >= size_)
  {
    throw std::out_of_range("the index is too large");
  }
  return shapeArray_[index];
}

double ryzhova::CompositeShape::getArea() const
{
  double area = 0;
  for (size_t i = 0; i < size_; i++)
  {
    area += shapeArray_[i]->getArea();
  }
  return area;
}

ryzhova::rectangle_t ryzhova::CompositeShape::getFrameRect() const
{
  if (size_ == 0)
  {
    throw std::length_error("shapeArray is empty");
  }
  rectangle_t rectangle = shapeArray_[0]->getFrameRect();
  double minX = rectangle.pos.x - rectangle.width / 2.0;
  double maxX = rectangle.pos.x + rectangle.width / 2.0;
  double minY = rectangle.pos.y - rectangle.height / 2.0;
  double maxY = rectangle.pos.y + rectangle.height / 2.0;
  if (size_ > 1)
  {
    for (size_t i = 1; i < size_; i++)
    {
      rectangle = shapeArray_[i]->getFrameRect();
      minX = std::min(minX, rectangle.pos.x - rectangle.width / 2.0);
      maxX = std::max(maxX, rectangle.pos.x + rectangle.width / 2.0);
      minY = std::min(minY, rectangle.pos.y - rectangle.height / 2.0);
      maxY = std::max(maxY, rectangle.pos.y + rectangle.height / 2.0);
    }
  }
  return {maxX - minX, maxY - minY, {(maxX + minX) / 2.0, (maxY + minY) / 2.0}};
}

void ryzhova::CompositeShape::move(double dx, double dy)
{
  if (size_ == 0)
  {
    throw std::length_error("shapeArray is empty");
  }
  for (size_t i = 0; i < size_; i++)
  {
    shapeArray_[i]->move(dx, dy);
  }
}

void ryzhova::CompositeShape::move(const ryzhova::point_t &centre)
{
  if (size_ == 0)
  {
    throw std::length_error("shapeArray is empty");
  }
  move(centre.x - getFrameRect().pos.x, centre.y - getFrameRect().pos.y);
}

void ryzhova::CompositeShape::scale(double coefficient)
{
  if (coefficient <= 0)
  {
    throw std::invalid_argument("not positive coefficient");
  }
  if (size_ == 0)
  {
    throw std::length_error("shapeArray is empty");
  }
  const point_t rectangleCentre = getFrameRect().pos;
  for (size_t i = 0; i < size_; i++)
  {
    const double shapeCentreDx = (shapeArray_[i]->getFrameRect().pos.x - rectangleCentre.x) * coefficient;
    const double shapeCentreDy = (shapeArray_[i]->getFrameRect().pos.y - rectangleCentre.y) * coefficient;
    shapeArray_[i]->move({rectangleCentre.x + shapeCentreDx, rectangleCentre.y + shapeCentreDy});
    shapeArray_[i]->scale(coefficient);
  }
}

void ryzhova::CompositeShape::print(std::ostream &out) const
{
  const rectangle_t temp = getFrameRect();
  out << "Border rectangle: height = " << temp.height << ", width = " << temp.width
      << ", centre.x = " << temp.pos.x << ", centre.y = " << temp.pos.y << "\n"
      << "Square: " << getArea() << "\n";
}

size_t ryzhova::CompositeShape::getSize() const
{
  return size_;
}
