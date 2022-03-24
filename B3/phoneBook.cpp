#include "phoneBook.hpp"

#include <stdexcept>

void PhoneBook::showRecord(PhoneBook::iterator it, std::ostream &out) const
{
  if (isEmpty())
  {
    throw std::logic_error("PhoneBook is empty");
  }
  out << it->number_ << " " << it->name_ << "\n";
}

void PhoneBook::insertBefore(std::list<PhoneBook::record_t>::iterator it, const PhoneBook::record_t &record)
{
  if (record.name_.empty() || record.number_.empty())
  {
    throw std::invalid_argument("Name or Number is Empty");
  }
  phoneBook_.insert(it, record);
}

void PhoneBook::insertAfter(PhoneBook::iterator it, const PhoneBook::record_t &record)
{
  if (record.name_.empty() || record.number_.empty())
  {
    throw std::invalid_argument("Name or Number is Empty");
  }
  it++;
  phoneBook_.insert(it, record);

}

void PhoneBook::replaceRecord(PhoneBook::iterator it, const PhoneBook::record_t &record)
{
  if (record.name_.empty() || record.number_.empty())
  {
    throw std::invalid_argument("Name or Number is Empty");
  }
  if (isEmpty())
  {
    throw std::logic_error("PhoneBook is empty");
  }
  phoneBook_.insert(phoneBook_.erase(it), record);
}

void PhoneBook::add(const PhoneBook::record_t &record)
{
  if (record.name_.empty() || record.number_.empty())
  {
    throw std::invalid_argument("Name or Number is Empty");
  }
  phoneBook_.push_back(record);
}

bool PhoneBook::isEmpty() const
{
  return phoneBook_.empty();
}

PhoneBook::iterator PhoneBook::erase(PhoneBook::iterator it)
{
  if (!isEmpty())
  {
    return phoneBook_.erase(it);
  }
  throw std::logic_error("Deleting from an empty phoneBook");
}

PhoneBook::iterator PhoneBook::begin()
{
  return phoneBook_.begin();
}

PhoneBook::iterator PhoneBook::end()
{
  return phoneBook_.end();
}

PhoneBook::const_iterator PhoneBook::begin() const
{
  return phoneBook_.cbegin();
}

PhoneBook::const_iterator PhoneBook::end() const
{
  return phoneBook_.cend();
}
