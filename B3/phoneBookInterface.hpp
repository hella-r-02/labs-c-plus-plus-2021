#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <map>

#include "phoneBook.hpp"

class PhoneBookInterface
{
public:
  enum  MovePos
  {
    first,
    last
  };
  PhoneBookInterface();
  void add(const PhoneBook::record_t &record);
  void store(std::ostream &out, const std::string &mark, const std::string &newMark);
  void insertBefore(std::ostream &out, const std::string &mark, const PhoneBook::record_t &record);
  void insertAfter(std::ostream &out, const std::string &mark, const PhoneBook::record_t &record);
  void deleteRecord(std::ostream &out, const std::string &mark);
  void show(std::ostream &out, const std::string &mark) const;
  void moveSteps(std::ostream &out, const std::string &mark, int step);
  void movePos(std::ostream &out, const std::string &mark, const MovePos& pos);
  void makeMarksValid();

private:
  PhoneBook phoneBook_;
  std::map<std::string, PhoneBook::iterator> mark_;
};

#endif
