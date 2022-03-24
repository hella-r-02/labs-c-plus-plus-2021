#include <iostream>

#include "circle.hpp"
#include "rectangle.hpp"

int main()
{
  try
  {
    const point_t centreRectangle = {3, 4};
    std::cout << "Creating a rectangle with height = 3, width = 2, center = (3;4)\n";
    Rectangle rectangle(centreRectangle, 2, 3);
    rectangle.print();
    std::cout << "\nCenter offset along the axes\n";
    rectangle.move(1, 2);
    std::cout << "After moving\n";
    rectangle.print();
    std::cout << "\nShifting the center to a specific point\n";
    rectangle.move({40, 50});
    std::cout << "After moving\n";
    rectangle.print();
  }
  catch (const std::invalid_argument &e)
  {
    std::cerr << "\n" << e.what() << "\n";
    return 1;
  }
  try
  {
    const point_t centreCircle = {25, 63};
    std::cout << "\n\nCreating a circle with radius = 4, center = (25,63)\n";
    Circle circle(centreCircle, 4);
    circle.print();
    std::cout << "\nCenter offset along the axes\n";
    circle.move(6, 10);
    std::cout << "After moving\n";
    circle.print();
    std::cout << "\nShifting the center to a specific point\n";
    circle.move({23, 5});
    std::cout << "After moving\n";
    circle.print();

  }
  catch (const std::invalid_argument &e)
  {
    std::cerr << "\n" << e.what() << "\n";
    return 1;
  }
  try
  {
    const point_t centreCircle2 = {-1, 28};
    std::cout << "\n\nCreating a circle with radius = 3, center = (-1,28)\n";
    Circle circle2(centreCircle2, 3);
    Shape &parentCircle2 = circle2;
    parentCircle2.print();
    std::cout << "\nCenter offset along the axes\n";
    parentCircle2.move(6, 10);
    std::cout << "After moving\n";
    parentCircle2.print();
    std::cout << "\nShifting the center to a specific point\n";
    parentCircle2.move({-1, 3});
    std::cout << "After moving\n";
    parentCircle2.print();
  }
  catch (const std::invalid_argument &e)
  {
    std::cerr << "\n" << e.what() << "\n";
    return 1;
  }
  return 0;
}
