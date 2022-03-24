#ifndef PHONE_BOOK_HPP
#define PHONE_BOOK_HPP

#include <ostream>
#include <list>

class PhoneBook
{
public:
  struct record_t
  {
    std::string number_;
    std::string name_;
  };

  using iterator = std::list<record_t>::iterator;
  using const_iterator = std::list<record_t>::const_iterator;

  void showRecord(iterator it, std::ostream &out) const;
  void insertBefore(iterator it, const record_t &record);
  void insertAfter(iterator it, const record_t &record);
  void replaceRecord(iterator it, const record_t &record);
  void add(const record_t &record);
  bool isEmpty() const;

  iterator begin();
  iterator end();

  const_iterator begin() const;
  const_iterator end() const;

  iterator erase(iterator it);

private:
  std::list<record_t> phoneBook_;

};
#endif
