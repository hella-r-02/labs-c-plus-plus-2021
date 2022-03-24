#include "parser.hpp"

#include <sstream>
#include <cctype>
#include <functional>
#include <map>
#include <string>
#include <stdexcept>

#include "phoneBook.hpp"
#include "phoneBookInterface.hpp"

std::string readNumber(std::istringstream &stream)
{
  std::string number;
  stream >> number;
  if (number.empty())
  {
    stream.setstate(std::ios::failbit);
    return number;
  }
  for (size_t i = 0; i < number.size(); i++)
  {
    if (!std::isdigit(number[i]))
    {
      stream.setstate(std::ios::failbit);
      break;
    }
  }
  return number;
}

std::string readName(std::istringstream &stream)
{
  std::string name;
  stream >> std::ws;
  char symbol;
  bool isEndReached = false;
  if (stream.peek() != '\"')
  {
    stream.setstate(std::ios::failbit);
    return name;
  }
  stream.get();

  while ((stream.peek() != '\n') && (stream.peek() != EOF))
  {
    symbol = stream.peek();
    if (symbol == '\\')
    {
      stream.get();
      if ((stream.peek() == '\"') || (stream.peek() == '\\'))
      {
        stream.get(symbol);
        name.push_back(symbol);
      }
      else
      {
        name.push_back(symbol);
      }
    }
    else if (symbol == '\"')
    {
      stream.get();
      isEndReached = true;
      break;
    }
    else
    {
      stream.get();
      name.push_back(symbol);
    }
  }
  if (!isEndReached)
  {
    stream.setstate(std::ios::failbit);
  }
  return name;
}

std::string readMark(std::istringstream &stream)
{
  std::string mark;
  stream >> mark;
  if (mark.empty())
  {
    stream.setstate(std::ios::failbit);
    return mark;
  }

  for (size_t i = 0; i < mark.size(); i++)
  {
    if (mark[i] != '-')
    {
      if (!std::isalnum(mark[i]))
      {
        stream.setstate(std::ios::failbit);
        return mark;
      }
    }
  }
  return mark;
}

CommandName parseAdd(std::istringstream &stream)
{
  const std::string number = readNumber(stream);
  if (!stream)
  {
    return &invalidCommand;
  }
  const std::string name = readName(stream);
  if (!stream)
  {
    return &invalidCommand;
  }
  if (isTrash(stream))
  {
    return &invalidCommand;
  }
  return std::bind(&PhoneBookInterface::add, std::placeholders::_1, PhoneBook::record_t{number, name});
}

CommandName parseStore(std::istringstream &stream)
{
  const std::string mark = readMark(stream);
  if (!stream)
  {
    return &invalidCommand;
  }
  const std::string newName = readMark(stream);
  if (!stream)
  {
    return &invalidCommand;
  }
  if (isTrash(stream))
  {
    return &invalidCommand;
  }
  return std::bind(&PhoneBookInterface::store, std::placeholders::_1, std::placeholders::_2, mark, newName);
}

CommandName parseInsert(std::istringstream &stream)
{
  std::string position;
  stream >> position;
  if (!stream)
  {
    return &invalidCommand;
  }
  const std::string mark = readMark(stream);
  if (!stream)
  {
    return &invalidCommand;
  }
  const std::string number = readNumber(stream);
  if (!stream)
  {
    return &invalidCommand;
  }
  const std::string name = readName(stream);
  if (!stream)
  {
    return &invalidCommand;
  }
  if (isTrash(stream))
  {
    return &invalidCommand;
  }
  if (position == "before")
  {
    return std::bind(&PhoneBookInterface::insertBefore, std::placeholders::_1, std::placeholders::_2, mark, PhoneBook::record_t{number, name});
  }
  if (position == "after")
  {
    return std::bind(&PhoneBookInterface::insertAfter, std::placeholders::_1, std::placeholders::_2, mark, PhoneBook::record_t{number, name});
  }
  return &invalidCommand;
}

CommandName parseDelete(std::istringstream &stream)
{
  const std::string mark = readMark(stream);
  if (!stream)
  {
    return &invalidCommand;
  }
  if (isTrash(stream))
  {
    return &invalidCommand;
  }
  return std::bind(&PhoneBookInterface::deleteRecord, std::placeholders::_1, std::placeholders::_2, mark);
}

CommandName parseShow(std::istringstream &stream)
{
  const std::string mark = readMark(stream);
  if (!stream)
  {
    return &invalidCommand;
  }
  if (isTrash(stream))
  {
    return &invalidCommand;
  }
  return std::bind(&PhoneBookInterface::show, std::placeholders::_1, std::placeholders::_2, mark);
}

CommandName parseMove(std::istringstream &stream)
{
  const std::string mark = readMark(stream);
  if (!stream)
  {
    return &invalidCommand;
  }
  std::string steps;
  stream >> steps;
  if (!stream)
  {
    throw std::runtime_error("Steps reading failed");
  }
  if (steps.empty())
  {
    return &invalidStep;

  }
  if (isTrash(stream))
  {
    return &invalidCommand;
  }
  if (steps == "first")
  {
    return std::bind(&PhoneBookInterface::movePos, std::placeholders::_1, std::placeholders::_2, mark, PhoneBookInterface::MovePos::first);
  }
  else if (steps == "last")
  {
    return std::bind(&PhoneBookInterface::movePos, std::placeholders::_1, std::placeholders::_2, mark, PhoneBookInterface::MovePos::last);
  }
  else
  {
    std::istringstream stream2(steps);
    int stepsCount = 0;
    stream2 >> stepsCount;
    if (!stream2.eof())
    {
      return &invalidStep;
    }
    return std::bind(&PhoneBookInterface::moveSteps, std::placeholders::_1, std::placeholders::_2, mark, stepsCount);
  }
}

CommandName parse(std::istringstream &stream)
{
  std::string command;
  stream >> command;
  if (!stream)
  {
    throw std::runtime_error("Command reading failed");
  }
  auto it = commands.find(command);
  if (it == commands.end())
  {
    return &invalidCommand;
  }
  return it->second(stream);
}

bool isTrash(std::istringstream &stream)
{
  std::string tempString;
  stream >> tempString;
  return (!tempString.empty());
}

void invalidCommand(PhoneBookInterface &, std::ostream &out)
{
  out << "<INVALID COMMAND>\n";
}

void invalidBookmark(std::ostream &out)
{
  out << "<INVALID BOOKMARK>\n";
}

void invalidStep(PhoneBookInterface &, std::ostream &out)
{
  out << "<INVALID STEP>\n";
}

void empty(std::ostream &out)
{
  out << "<EMPTY>\n";
}
