#include <stdexcept>

#include <boost/test/unit_test.hpp>

#include "phoneBook.hpp"

const std::string name1 = "Alena";
const std::string name2 = "Vasya";
const std::string name3 = "Petr";
const std::string name4 = "Manya";

const std::string number1 = "123456789";
const std::string number2 = "12345";
const std::string number3 = "2948191";
const std::string number4 = "93817361";

const std::string invalidName = "";
const std::string invalidNumber = "";

BOOST_AUTO_TEST_SUITE(test_phoneBook)

struct Fixture
{
  PhoneBook book;
  const PhoneBook::record_t record1;
  const PhoneBook::record_t record2;
  const PhoneBook::record_t record3;
  const PhoneBook::record_t record4;
  const PhoneBook::record_t recordInvalid1;
  const PhoneBook::record_t recordInvalid2;
  const PhoneBook::record_t recordInvalid3;
  PhoneBook::iterator iterator;

  Fixture() :
    record1{number1, name1},
    record2{number2, name2},
    record3{number3, name3},
    record4{number4, name4},
    recordInvalid1{invalidNumber, invalidName},
    recordInvalid2{number1, invalidName},
    recordInvalid3{invalidNumber, name1}
  {
    book.add(record1);
    book.add(record2);
  }
};

BOOST_FIXTURE_TEST_CASE(test_begin_and_end, Fixture)
{
  std::string a = book.begin()->name_;
  BOOST_CHECK_EQUAL(book.begin()->name_, name1);
  BOOST_CHECK_EQUAL(book.begin()->number_, number1);
  BOOST_CHECK_EQUAL(std::prev(book.end())->name_, name2);
  BOOST_CHECK_EQUAL(std::prev(book.end())->number_, number2);
}

BOOST_FIXTURE_TEST_CASE(test_add, Fixture)
{
  book.add(record3);
  iterator = book.begin();
  BOOST_CHECK_EQUAL(name1, iterator->name_);
  BOOST_CHECK_EQUAL(number1, iterator->number_);

  iterator++;
  BOOST_CHECK_EQUAL(name2, iterator->name_);
  BOOST_CHECK_EQUAL(number2, iterator->number_);

  iterator++;
  BOOST_CHECK_EQUAL(name3, iterator->name_);
  BOOST_CHECK_EQUAL(number3, iterator->number_);

  BOOST_CHECK_THROW(book.add(recordInvalid1), std::invalid_argument);
  BOOST_CHECK_THROW(book.add(recordInvalid2), std::invalid_argument);
  BOOST_CHECK_THROW(book.add(recordInvalid3), std::invalid_argument);

}

BOOST_FIXTURE_TEST_CASE(test_is_empty, Fixture)
{
  PhoneBook book2;
  BOOST_CHECK_EQUAL(book2.isEmpty(), true);

  book2.add(record1);
  BOOST_CHECK_EQUAL(book2.isEmpty(), false);
}

BOOST_FIXTURE_TEST_CASE(test_erase, Fixture)
{
  iterator = book.begin();
  book.erase(iterator);
  iterator = book.begin();
  book.erase(iterator);
  BOOST_CHECK_EQUAL(book.isEmpty(), true);

  book.add(record1);
  book.add(record2);
  iterator = book.begin();
  book.erase(iterator);
  BOOST_CHECK_EQUAL(book.isEmpty(), false);

  iterator = book.begin();
  BOOST_CHECK_EQUAL(iterator->name_, name2);
  BOOST_CHECK_EQUAL(iterator->number_, number2);

  book.add(record1);
  book.add(record3);
  iterator = book.begin();
  iterator++;
  book.erase(iterator);
  iterator = book.begin();
  BOOST_CHECK_EQUAL(iterator->name_, name2);
  BOOST_CHECK_EQUAL(iterator->number_, number2);

  iterator++;
  BOOST_CHECK_EQUAL(iterator->name_, name3);
  BOOST_CHECK_EQUAL(iterator->number_, number3);

  iterator = book.begin();
  iterator++;
  book.erase(iterator);
  iterator = book.begin();
  BOOST_CHECK_EQUAL(iterator->name_, name2);
  BOOST_CHECK_EQUAL(iterator->number_, number2);

  PhoneBook book2;
  iterator = book2.begin();
  BOOST_CHECK_THROW(book2.erase(iterator), std::logic_error);
}

BOOST_FIXTURE_TEST_CASE(test_insert, Fixture)
{
  iterator = book.begin();
  iterator++;
  book.insertBefore(iterator, record3);
  iterator = book.begin();
  BOOST_CHECK_EQUAL(name1, iterator->name_);
  BOOST_CHECK_EQUAL(number1, iterator->number_);

  iterator++;
  BOOST_CHECK_EQUAL(name3, iterator->name_);
  BOOST_CHECK_EQUAL(number3, iterator->number_);

  iterator++;
  BOOST_CHECK_EQUAL(name2, iterator->name_);
  BOOST_CHECK_EQUAL(number2, iterator->number_);

  iterator--;
  book.insertAfter(iterator, record4);
  iterator = book.begin();
  BOOST_CHECK_EQUAL(name1, iterator->name_);
  BOOST_CHECK_EQUAL(number1, iterator->number_);

  iterator++;
  BOOST_CHECK_EQUAL(name3, iterator->name_);
  BOOST_CHECK_EQUAL(number3, iterator->number_);

  iterator++;
  BOOST_CHECK_EQUAL(name4, iterator->name_);
  BOOST_CHECK_EQUAL(number4, iterator->number_);

  iterator++;
  BOOST_CHECK_EQUAL(name2, iterator->name_);
  BOOST_CHECK_EQUAL(number2, iterator->number_);

  BOOST_CHECK_THROW(book.insertAfter(iterator, recordInvalid1), std::invalid_argument);
  BOOST_CHECK_THROW(book.insertAfter(iterator, recordInvalid2), std::invalid_argument);
  BOOST_CHECK_THROW(book.insertAfter(iterator, recordInvalid3), std::invalid_argument);
  BOOST_CHECK_THROW(book.insertBefore(iterator, recordInvalid1), std::invalid_argument);
  BOOST_CHECK_THROW(book.insertBefore(iterator, recordInvalid2), std::invalid_argument);
  BOOST_CHECK_THROW(book.insertBefore(iterator, recordInvalid3), std::invalid_argument);
}

BOOST_FIXTURE_TEST_CASE(test_replase, Fixture)
{
  iterator = book.begin();
  iterator++;
  book.replaceRecord(iterator, record3);
  iterator = book.begin();
  BOOST_CHECK_EQUAL(name1, iterator->name_);
  BOOST_CHECK_EQUAL(number1, iterator->number_);

  iterator++;
  BOOST_CHECK_EQUAL(name3, iterator->name_);
  BOOST_CHECK_EQUAL(number3, iterator->number_);

  BOOST_CHECK_THROW(book.replaceRecord(iterator, recordInvalid1), std::invalid_argument);
  BOOST_CHECK_THROW(book.replaceRecord(iterator, recordInvalid2), std::invalid_argument);
  BOOST_CHECK_THROW(book.replaceRecord(iterator, recordInvalid3), std::invalid_argument);

  PhoneBook book2;
  BOOST_CHECK_THROW(book2.replaceRecord(iterator, record3), std::logic_error);
}

BOOST_FIXTURE_TEST_CASE(test_show, Fixture)
{
  std::ostringstream outputStream;
  iterator = book.begin();
  book.showRecord(iterator, outputStream);
  BOOST_CHECK_EQUAL(outputStream.str(), number1 + " " + name1 + "\n");
  PhoneBook book2;
  iterator = book2.begin();
  BOOST_CHECK_THROW(book2.showRecord(iterator, outputStream), std::logic_error);
}

BOOST_AUTO_TEST_SUITE_END()
