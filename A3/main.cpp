#include <iostream>
#include <memory>
#include <stdexcept>

#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"

int main()
{
  try
  {
    std::cout << "Creating a rectangle with height = 3, width = 2, center = (3;4)\n";
    ryzhova::Rectangle rectangle({3,4}, 2, 3);
    rectangle.print(std::cout);
    std::cout<<"After scaling (coefficient = 10.5)\n";
    rectangle.scale(0.5);
    rectangle.print(std::cout);
  }
  catch (const std::invalid_argument &e)
  {
    std::cerr << "\n" << e.what() << "\n";
    return 1;
  }
  try
  {
    std::cout << "\n\nCreating a circle with radius = 4, center = (25,63)\n";
    ryzhova::Circle circle({25,63}, 4);
    circle.print(std::cout);
    std::cout<<"After scaling (coefficient = 1.6)\n";
    circle.scale(1.6);
    circle.print(std::cout);
  }
  catch (const std::invalid_argument &e)
  {
    std::cerr << "\n" << e.what() << "\n";
    return 1;
  }

  try
  {
    std::cout << "\n\nCreating a circle with radius = 3, center = (-1,28)\n";
    ryzhova::Circle circle2({-1,28}, 3);
    ryzhova::Shape &parentCircle2 = circle2;
    parentCircle2.print(std::cout);
    std::cout<<"After scaling (coefficient = 0.5)\n";
    parentCircle2.scale(0.5);
    parentCircle2.print(std::cout);
  }
  catch (const std::invalid_argument &e)
  {
    std::cerr << "\n" << e.what() << "\n";
    return 1;
  }

  const ryzhova::Rectangle rectangle1({-1.2, 2.3}, 3.2, 2.3);
  const ryzhova::Rectangle rectangle2({5.6, 8.1}, 4.2, 1.3);
  const ryzhova::Circle circle1({1.5, -4.5}, 7.4);
  const ryzhova::Circle circle2({8.9, 7.6}, 5.4);
  ryzhova::CompositeShape compositeShape;

  try
  {
    std::cout<<"\nCreate composite Shape\n";
    compositeShape.addShape(std::make_shared<ryzhova::Rectangle>(rectangle1));
    compositeShape.addShape(std::make_shared<ryzhova::Rectangle>(rectangle2));
    compositeShape.addShape(std::make_shared<ryzhova::Circle>(circle1));
    compositeShape.addShape(std::make_shared<ryzhova::Circle>(circle2));
    compositeShape.addShape(std::make_shared<ryzhova::Circle>(circle2));
    compositeShape.print(std::cout);
  }
  catch(const std::invalid_argument &error)
  {
    std::cerr<<"\n" << error.what() << "\n";
    return 1;
  }

  try
  {
    compositeShape.move(-2.2,-3.8);
    std::cout<<"\nAfter move (dx =-2.2 , dy = -3.8):\n";
    compositeShape.print(std::cout);
  }
  catch(const std::length_error &error)
  {
    std::cerr << "\n" << error.what() << "\n";
    return 1;
  }

  try
  {
    compositeShape.move({-4.4,-4.3});
    std::cout<<"\nAfter move (x = -4.4 , y = -4.3):\n";
    compositeShape.print(std::cout);
  }
  catch(const std::length_error &error)
  {
    std::cerr << "\n" << error.what() << "\n";
    return 1;
  }
  try
  {
    compositeShape.scale(2.4);
    std::cout<<"\nAfter scaling (coefficient = 2.4)\n";
    compositeShape.print(std::cout);
  }
  catch (const std::length_error &error)
  {
    std::cerr << "\n" << error.what() << "\n";
    return 1;
  }
  catch(const std::invalid_argument &error)
  {
    std::cerr<<"\n" << error.what() << "\n";
    return 1;
  }
  try
  {
    compositeShape.deleteShape(1);
    std::cout<<"After deletion\n";
    compositeShape.print(std::cout);
  }
  catch (const std::length_error &error)
  {
    std::cerr << "\n" << error.what() << "\n";
    return 1;
  }
  catch(const std::out_of_range &error)
  {
    std::cerr<<"\n"<<error.what()<<"\n";
  }
  return 0;
}
