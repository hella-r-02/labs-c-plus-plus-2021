#include "phoneBookInterface.hpp"

#include <ostream>
#include <iterator>

#include "parser.hpp"
#include "phoneBook.hpp"

PhoneBookInterface::PhoneBookInterface()
{
  mark_["current"] = phoneBook_.begin();
}

void PhoneBookInterface::add(const PhoneBook::record_t &record)
{
  phoneBook_.add(record);
  if (phoneBook_.begin() == std::prev(phoneBook_.end()))
  {
    makeMarksValid();
  }
}

void PhoneBookInterface::store(std::ostream &out, const std::string &mark, const std::string &newMark)
{
  auto it = mark_.find(mark);
  if (it == mark_.end())
  {
    invalidBookmark(out);
    return;
  }

  mark_[newMark] = it->second;
}

void PhoneBookInterface::insertBefore(std::ostream &out, const std::string &mark, const PhoneBook::record_t &record)
{
  auto it = mark_.find(mark);
  if (it == mark_.end())
  {
    invalidBookmark(out);
    return;
  }
  if (phoneBook_.isEmpty())
  {
    add(record);
    return;
  }

  phoneBook_.insertBefore(it->second, record);
  if (phoneBook_.begin() == std::prev(phoneBook_.end()))
  {
    makeMarksValid();
  }
}

void PhoneBookInterface::insertAfter(std::ostream &out, const std::string &mark, const PhoneBook::record_t &record)
{
  auto it = mark_.find(mark);
  if (it == mark_.end())
  {
    invalidBookmark(out);
    return;
  }
  if (it->second == phoneBook_.end())
  {
    add(record);
    return;
  }
  phoneBook_.insertAfter(it->second, record);
  if (phoneBook_.begin() == std::prev(phoneBook_.end()))
  {
    makeMarksValid();
  }
}

void PhoneBookInterface::deleteRecord(std::ostream &out, const std::string &mark)
{
  if (phoneBook_.isEmpty())
  {
    empty(out);
    return;
  }
  auto markFind = mark_.find(mark);
  if (markFind == mark_.end())
  {
    invalidBookmark(out);
    return;
  }
  auto temp = markFind->second;
  auto it = mark_.begin();
  while (it != mark_.end())
  {
    if (it->second == temp)
    {
      if ((std::next(temp) == phoneBook_.end()) && (temp != phoneBook_.begin()))
      {
        it->second--;
      }
      else
      {
        it->second++;
      }
    }
    it++;
  }
  phoneBook_.erase(temp);
}

void PhoneBookInterface::show(std::ostream &out, const std::string &mark) const
{
  auto it = mark_.find(mark);
  if (it == mark_.end())
  {
    invalidBookmark(out);
    return;
  }
  if (phoneBook_.isEmpty())
  {
    empty(out);
    return;
  }
  out << it->second->number_ << " " << it->second->name_ << "\n";
}

void PhoneBookInterface::moveSteps(std::ostream &out, const std::string &mark, int step)
{
  if (phoneBook_.isEmpty())
  {
    empty(out);
    return;
  }
  auto it = mark_.find(mark);
  if (it == mark_.end())
  {
    invalidBookmark(out);
    return;
  }
  if ((step > 0) && (std::distance(it->second, --phoneBook_.end()) >= step))
  {
    std::advance(it->second, step);
  }
  else if ((step < 0) && (std::distance(phoneBook_.begin(), it->second) >= -step))
  {
    std::advance(it->second, step);
  }
}

void PhoneBookInterface::makeMarksValid()
{
  auto it = mark_.begin();
  for (it = mark_.begin(); it != mark_.end(); it++)
  {
    it->second = phoneBook_.begin();
  }
}

void PhoneBookInterface::movePos(std::ostream &out, const std::string &mark, const PhoneBookInterface::MovePos &pos)
{
  if (phoneBook_.isEmpty())
  {
    empty(out);
    return;
  }
  auto it = mark_.find(mark);
  if (it == mark_.end())
  {
    invalidBookmark(out);
    return;
  }

  if (pos == MovePos::first)
  {
    it->second = phoneBook_.begin();
  }
  else if (pos == MovePos::last)
  {
    it->second = std::prev(phoneBook_.end());

  }
}
