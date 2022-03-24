#include <iostream>
#include <iterator>

#include "phoneBookInterface.hpp"
#include "parser.hpp"

void task1(std::istream &in, std::ostream &out)
{
  std::string input;
  PhoneBookInterface phoneBook;
  while (std::getline(in, input))
  {
    std::istringstream stream(input);
    if ((stream >> std::ws).eof())
    {
      continue;
    }
    CommandName command = parse(stream);
    command(phoneBook, out);
  }
}
