#include <stdexcept>

#include <boost/test/unit_test.hpp>

#include "phoneBook.hpp"
#include "phoneBookInterface.hpp"

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

const std::string INVALIDBOOKMARK = "<INVALID BOOKMARK>\n";
const std::string INVALIDSTEP = "<INVALID STEP>\n";
const std::string EMPTY = "<EMPTY>\n";

const std::string defaultMark = "current";
const std::string invalidMark = "123";
const std::string mark2 = "school";

BOOST_AUTO_TEST_SUITE(test_interface)
struct Fixture
{
  Fixture() :
    record1{number1, name1},
    record2{number2, name2},
    record3{number3, name3},
    record4{number4, name4},
    interface(),
    emptyInterface()
  {
    interface.add(record1);
    interface.add(record2);
  }
  const PhoneBook::record_t record1;
  const PhoneBook::record_t record2;
  const PhoneBook::record_t record3;
  const PhoneBook::record_t record4;
  PhoneBookInterface interface;
  PhoneBookInterface emptyInterface;
};

BOOST_FIXTURE_TEST_CASE(test_show, Fixture)
{
  std::ostringstream outputStream;
  interface.show(outputStream, defaultMark);
  BOOST_CHECK_EQUAL(outputStream.str(), number1 + " " + name1 + "\n");

  std::ostringstream outputStream2;
  emptyInterface.show(outputStream2, defaultMark);
  BOOST_CHECK_EQUAL(outputStream2.str(), EMPTY);

  std::ostringstream outputStream3;
  interface.show(outputStream3, invalidMark);
  BOOST_CHECK_EQUAL(outputStream3.str(), INVALIDBOOKMARK);
}

BOOST_FIXTURE_TEST_CASE(test_move_pos, Fixture)
{
  std::ostringstream outputStream;
  interface.movePos(outputStream, defaultMark, PhoneBookInterface::last);
  interface.show(outputStream, defaultMark);
  BOOST_CHECK_EQUAL(outputStream.str(), number2 + " " + name2 + "\n");
  interface.movePos(outputStream, defaultMark, PhoneBookInterface::first);

  std::ostringstream outputStream2;
  interface.show(outputStream2, defaultMark);
  BOOST_CHECK_EQUAL(outputStream2.str(), number1 + " " + name1 + "\n");

  std::ostringstream outputStream3;
  interface.movePos(outputStream3, invalidMark, PhoneBookInterface::first);
  BOOST_CHECK_EQUAL(outputStream3.str(), INVALIDBOOKMARK);

  std::ostringstream outputStream5;
  emptyInterface.movePos(outputStream5, defaultMark, PhoneBookInterface::last);
  BOOST_CHECK_EQUAL(outputStream5.str(), EMPTY);
}

BOOST_FIXTURE_TEST_CASE(test_move_step, Fixture)
{
  std::ostringstream outputStream;
  interface.moveSteps(outputStream, defaultMark, 1);
  interface.show(outputStream, defaultMark);
  BOOST_CHECK_EQUAL(outputStream.str(), number2 + " " + name2 + "\n");

  std::ostringstream outputStream2;
  interface.moveSteps(outputStream2, defaultMark, -1);
  interface.show(outputStream2, defaultMark);
  BOOST_CHECK_EQUAL(outputStream2.str(), number1 + " " + name1 + "\n");

  std::ostringstream outputStream3;
  emptyInterface.moveSteps(outputStream3, defaultMark, 1);
  BOOST_CHECK_EQUAL(outputStream3.str(), EMPTY);
}

BOOST_FIXTURE_TEST_CASE(test_add, Fixture)
{
  std::ostringstream outputStream;
  interface.add(record3);
  interface.movePos(outputStream, defaultMark, PhoneBookInterface::last);
  interface.show(outputStream, defaultMark);
  BOOST_CHECK_EQUAL(outputStream.str(), number3 + " " + name3 + "\n");
}

BOOST_FIXTURE_TEST_CASE(test_insert, Fixture)
{
  std::ostringstream outputStream;
  interface.insertBefore(outputStream, defaultMark, record3);
  interface.movePos(outputStream, defaultMark, PhoneBookInterface::first);
  interface.show(outputStream, defaultMark);
  BOOST_CHECK_EQUAL(outputStream.str(), number3 + " " + name3 + "\n");

  std::ostringstream outputStream2;
  interface.insertAfter(outputStream2, defaultMark, record4);
  interface.moveSteps(outputStream2, defaultMark, 1);
  interface.show(outputStream2, defaultMark);
  BOOST_CHECK_EQUAL(outputStream2.str(), number4 + " " + name4 + "\n");

  std::ostringstream outputStream3;
  emptyInterface.insertBefore(outputStream3, defaultMark, record1);
  emptyInterface.movePos(outputStream3, defaultMark, PhoneBookInterface::first);
  emptyInterface.show(outputStream3, defaultMark);
  BOOST_CHECK_EQUAL(outputStream3.str(), number1 + " " + name1 + "\n");

  std::ostringstream outputStream4;
  emptyInterface.insertAfter(outputStream4, defaultMark, record1);
  emptyInterface.movePos(outputStream4, defaultMark, PhoneBookInterface::last);
  emptyInterface.show(outputStream4, defaultMark);
  BOOST_CHECK_EQUAL(outputStream4.str(), number1 + " " + name1 + "\n");

  std::ostringstream outputStream5;
  interface.insertAfter(outputStream5, invalidMark, record1);
  BOOST_CHECK_EQUAL(outputStream5.str(), INVALIDBOOKMARK);

  std::ostringstream outputStream6;
  interface.insertBefore(outputStream6, invalidMark, record1);
  BOOST_CHECK_EQUAL(outputStream6.str(), INVALIDBOOKMARK);
}

BOOST_FIXTURE_TEST_CASE(test_store, Fixture)
{
  std::ostringstream outputStream;
  interface.show(outputStream, defaultMark);

  std::ostringstream outputStream2;
  interface.store(outputStream2, defaultMark, mark2);
  interface.show(outputStream2, mark2);
  BOOST_CHECK_EQUAL(outputStream2.str(), outputStream2.str());

  std::ostringstream outputStream3;
  interface.store(outputStream3, invalidMark, mark2);
  BOOST_CHECK_EQUAL(outputStream3.str(), INVALIDBOOKMARK);
}

BOOST_FIXTURE_TEST_CASE(test_delete_record, Fixture)
{
  std::ostringstream outputStream;
  interface.deleteRecord(outputStream, defaultMark);
  interface.show(outputStream, defaultMark);
  BOOST_CHECK_EQUAL(outputStream.str(), number2 + " " + name2 + "\n");

  std::ostringstream outputStream2;
  emptyInterface.deleteRecord(outputStream2, defaultMark);
  BOOST_CHECK_EQUAL(outputStream2.str(), EMPTY);

  std::ostringstream outputStream3;
  interface.deleteRecord(outputStream3, invalidMark);
  BOOST_CHECK_EQUAL(outputStream3.str(), INVALIDBOOKMARK);
}

BOOST_AUTO_TEST_SUITE_END()
