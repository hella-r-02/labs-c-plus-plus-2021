#include<stdexcept>

#include <boost/test/unit_test.hpp>

#include "phoneBook.hpp"
#include "parser.hpp"

const std::string number1 = "19337329";
const std::string invalidNumber1 = "139as20";

const std::string name1 = "\"Alena\"";
const std::string name2 = "\"Al\\\"e\\\"na\"";
const std::string name3 = "\"\\\\A\\\"le\\\\na\\\"\"";
const std::string name4 = "\"Alena Ryzhova\"";
const std::string invalidName1 = "Alena";
const std::string invalidName2 = "\"Alena";
const std::string invalidName3 = "Alena\"";
const std::string outName1 = "Alena";
const std::string outName2 = "Al\"e\"na";
const std::string outName3 = "\\A\"le\\na\"";
const std::string outName4 = "Alena Ryzhova";

const std::string commandAdd = "add 234421 \"Alena\"";
const std::string invalidCommandAdd1 = "add ";
const std::string invalidCommandAdd2 = "add 123";
const std::string invalidCommandAdd3 = "add 12a3w ";
const std::string invalidCommandAdd4 = "add 1234 \"Alena\n";
const std::string invalidCommandAdd5 = "add 1234 \"Alena\" sksjd";

const std::string invalidCommandStore1 = "store";
const std::string invalidCommandStore2 = "store current";
const std::string invalidCommandStore3 = "store mark newMark";
const std::string invalidCommandStore4 = "store current &mark";
const std::string commandStore1 = "store current mArk";
const std::string commandStore2 = "store current mArk4";
const std::string commandStore3 = "store current mark-work";

const std::string invalidCommandInsertBefore1 = "insert";
const std::string invalidCommandInsertBefore2 = "insert before ";
const std::string invalidCommandInsertBefore3 = "insert before mark ";
const std::string invalidCommandInsertBefore4 = "insert before mark 123";
const std::string invalidCommandInsertBefore5 = "insert before mark 1929 \"ALena\"";
const std::string commandInsertBefore = "insert before current 1929 \"ALena\"";

const std::string invalidCommandInsertAfter1 = "insert";
const std::string invalidCommandInsertAfter2 = "insert after ";
const std::string invalidCommandInsertAfter3 = "insert after mark ";
const std::string invalidCommandInsertAfter4 = "insert after mark 123";
const std::string invalidCommandInsertAfter5 = "insert after mark 1929 \"ALena\" ";
const std::string commandInsertAfter = "insert after current 1929 \"ALena\"";

const std::string invalidCommandDelete1 = "delete";
const std::string invalidCommandDelete2 = "delete mark";
const std::string commandDelete = "delete current";

const std::string invalidCommandShow1 = "show";
const std::string invalidCommandShow2 = "show mark";
const std::string commandShow = "show current";
const std::string showOut = "19337329 \"Alena\"\n";

const std::string invalidCommandMove1 = "move";
const std::string invalidCommandMove2 = "move mark";
const std::string invalidCommandMove3 = "move mark first";
const std::string invalidCommandMove4 = "move mark last";
const std::string invalidCommandMove5 = "move mark 5";
const std::string invalidCommandMove6 = "move current 3";
const std::string commandMove1 = "move current first";
const std::string commandMove2 = "move current last";
const std::string commandMove3 = "move current -1";
const std::string commandMove4 = "move current 1";

const std::string INVALIDCOMMAND = "<INVALID COMMAND>\n";
const std::string INVALIDBOOKMARK = "<INVALID BOOKMARK>\n";
const std::string EMPTY = "<EMPTY>\n";
const std::string INVALIDSTEP = "<INVALID STEP>\n";
const std::string number2 = "2948191";

BOOST_AUTO_TEST_SUITE(test_parcer)

struct Fixture
{
  Fixture() :
    record1{number1, name1},
    record2{number2, name2},
    interface(),
    emptyInterface()
  {
    interface.add(record1);
    interface.add(record2);
  }

  const PhoneBook::record_t record1;
  const PhoneBook::record_t record2;
  PhoneBookInterface interface;
  PhoneBookInterface emptyInterface;
};

BOOST_AUTO_TEST_CASE(test_read_number)
{
  std::istringstream stream;
  stream.str(number1);
  std::string tempNumber = readNumber(stream);
  BOOST_CHECK_EQUAL(tempNumber, number1);

  std::istringstream stream2;
  stream2.str(invalidNumber1);
  tempNumber = readNumber(stream2);
  BOOST_CHECK_EQUAL(tempNumber, invalidNumber1);
}

BOOST_FIXTURE_TEST_CASE(test_read_name, Fixture)
{
  std::istringstream stream;
  stream.str(name1);
  std::string tempName = readName(stream);
  BOOST_CHECK_EQUAL(tempName, outName1);

  std::istringstream stream2;
  stream2.str(name2);
  tempName = readName(stream2);
  BOOST_CHECK_EQUAL(tempName, outName2);

  std::istringstream stream3;
  stream3.str(name3);
  tempName = readName(stream3);
  BOOST_CHECK_EQUAL(tempName, outName3);

  std::istringstream stream4;
  stream4.str(name4);
  tempName = readName(stream4);
  BOOST_CHECK_EQUAL(tempName, outName4);

  std::istringstream stream5;
  stream5.str(invalidName1);
  tempName = readName(stream5);
  BOOST_CHECK(!stream5);

  std::istringstream stream6;
  stream6.str(invalidName2);
  tempName = readName(stream6);
  BOOST_CHECK(!stream6);

  std::istringstream stream7;
  stream7.str(invalidName3);
  tempName = readName(stream7);
  BOOST_CHECK(!stream7);
}

BOOST_FIXTURE_TEST_CASE(test_add, Fixture)
{
  std::istringstream stream;
  std::ostringstream outputStream;
  stream.str(invalidCommandAdd1);
  CommandName command = parse(stream);
  command(interface, outputStream);
  BOOST_CHECK_EQUAL(outputStream.str(), INVALIDCOMMAND);

  std::istringstream stream2;
  std::ostringstream outputStream2;
  stream2.str(invalidCommandAdd2);
  command = parse(stream2);
  command(interface, outputStream2);
  BOOST_CHECK_EQUAL(outputStream2.str(), INVALIDCOMMAND);

  std::istringstream stream3;
  std::ostringstream outputStream3;
  stream3.str(invalidCommandAdd3);
  command = parse(stream3);
  command(interface, outputStream3);
  BOOST_CHECK_EQUAL(outputStream3.str(), INVALIDCOMMAND);

  std::istringstream stream4;
  std::ostringstream outputStream4;
  stream4.str(invalidCommandAdd4);
  command = parse(stream4);
  command(interface, outputStream4);
  BOOST_CHECK_EQUAL(outputStream4.str(), INVALIDCOMMAND);

  std::istringstream stream5;
  std::ostringstream outputStream5;
  stream5.str(invalidCommandAdd5);
  command = parse(stream5);
  command(interface, outputStream5);
  BOOST_CHECK_EQUAL(outputStream5.str(), INVALIDCOMMAND);

  std::istringstream stream6;
  std::ostringstream outputStream6;
  stream6.str(commandAdd);
  command = parse(stream6);
  BOOST_CHECK_NO_THROW(command(interface, outputStream6));
}

BOOST_FIXTURE_TEST_CASE(test_store, Fixture)
{
  std::istringstream stream;
  std::ostringstream outputStream;
  stream.str(invalidCommandStore1);
  CommandName command = parse(stream);
  command(interface, outputStream);
  BOOST_CHECK_EQUAL(outputStream.str(), INVALIDCOMMAND);

  std::istringstream stream2;
  std::ostringstream outputStream2;
  stream2.str(invalidCommandStore2);
  command = parse(stream2);
  command(interface, outputStream2);
  BOOST_CHECK_EQUAL(outputStream2.str(), INVALIDCOMMAND);

  std::istringstream stream3;
  std::ostringstream outputStream3;
  stream3.str(invalidCommandStore3);
  command = parse(stream3);
  command(interface, outputStream3);
  BOOST_CHECK_EQUAL(outputStream3.str(), INVALIDBOOKMARK);

  std::istringstream stream4;
  std::ostringstream outputStream4;
  stream4.str(invalidCommandStore4);
  command = parse(stream4);
  command(interface, outputStream4);
    BOOST_CHECK_EQUAL(outputStream4.str(), INVALIDCOMMAND);

  std::istringstream stream5;
  std::ostringstream outputStream5;
  stream5.str(commandStore1);
  command = parse(stream5);
  BOOST_CHECK_NO_THROW(command(interface, outputStream5));

  std::istringstream stream6;
  std::ostringstream outputStream6;
  stream6.str(commandStore2);
  command = parse(stream6);
  BOOST_CHECK_NO_THROW(command(interface, outputStream6));

  std::istringstream stream7;
  std::ostringstream outputStream7;
  stream7.str(commandStore3);
  command = parse(stream7);
  BOOST_CHECK_NO_THROW(command(interface, outputStream6));
}

BOOST_FIXTURE_TEST_CASE(test_insert_before, Fixture)
{
  std::istringstream stream;
  std::ostringstream outputStream;
  stream.str(invalidCommandInsertBefore1);
  CommandName command = parse(stream);
  command(interface, outputStream);
  BOOST_CHECK_EQUAL(outputStream.str(), INVALIDCOMMAND);

  std::istringstream stream2;
  std::ostringstream outputStream2;
  stream2.str(invalidCommandInsertBefore2);
  command = parse(stream2);
  command(interface, outputStream2);
  BOOST_CHECK_EQUAL(outputStream2.str(), INVALIDCOMMAND);

  std::istringstream stream3;
  std::ostringstream outputStream3;
  stream3.str(invalidCommandInsertBefore3);
  command = parse(stream3);
  command(interface, outputStream3);
  BOOST_CHECK_EQUAL(outputStream3.str(), INVALIDCOMMAND);

  std::istringstream stream4;
  std::ostringstream outputStream4;
  stream4.str(invalidCommandInsertBefore4);
  command = parse(stream4);
  command(interface, outputStream4);
  BOOST_CHECK_EQUAL(outputStream4.str(), INVALIDCOMMAND);

  std::istringstream stream5;
  std::ostringstream outputStream5;
  stream5.str(invalidCommandInsertBefore5);
  command = parse(stream5);
  command(interface, outputStream5);
  BOOST_CHECK_EQUAL(outputStream5.str(), INVALIDBOOKMARK);

  std::istringstream stream6;
  std::ostringstream outputStream6;
  stream6.str(commandInsertBefore);
  command = parse(stream6);
  BOOST_CHECK_NO_THROW(command(interface, outputStream6));
}

BOOST_FIXTURE_TEST_CASE(test_insert_after, Fixture)
{
  std::istringstream stream;
  std::ostringstream outputStream;
  stream.str(invalidCommandInsertAfter1);
  CommandName command = parse(stream);
  command(interface, outputStream);
  BOOST_CHECK_EQUAL(outputStream.str(), INVALIDCOMMAND);

  std::istringstream stream2;
  std::ostringstream outputStream2;
  stream2.str(invalidCommandInsertAfter2);
  command = parse(stream2);
  command(interface, outputStream2);
  BOOST_CHECK_EQUAL(outputStream2.str(), INVALIDCOMMAND);

  std::istringstream stream3;
  std::ostringstream outputStream3;
  stream3.str(invalidCommandInsertAfter3);
  command = parse(stream3);
  command(interface, outputStream3);
  BOOST_CHECK_EQUAL(outputStream3.str(), INVALIDCOMMAND);

  std::istringstream stream4;
  std::ostringstream outputStream4;
  stream4.str(invalidCommandInsertAfter4);
  command = parse(stream4);
  command(interface, outputStream4);
  BOOST_CHECK_EQUAL(outputStream4.str(), INVALIDCOMMAND);

  std::istringstream stream5;
  std::ostringstream outputStream5;
  stream5.str(invalidCommandInsertAfter5);
  command = parse(stream5);
  command(interface, outputStream5);
  BOOST_CHECK_EQUAL(outputStream5.str(), INVALIDBOOKMARK);

  std::istringstream stream6;
  std::ostringstream outputStream6;
  stream6.str(commandInsertAfter);
  command = parse(stream6);
  BOOST_CHECK_NO_THROW(command(interface, outputStream6));
}

BOOST_FIXTURE_TEST_CASE(test_delete, Fixture)
{

  std::istringstream stream;
  std::ostringstream outputStream;
  stream.str(invalidCommandDelete1);
  CommandName command = parse(stream);
  command(interface, outputStream);
  BOOST_CHECK_EQUAL(outputStream.str(), INVALIDCOMMAND);

  std::istringstream stream2;
  std::ostringstream outputStream2;
  stream2.str(invalidCommandDelete2);
  command = parse(stream2);
  command(interface, outputStream2);
  BOOST_CHECK_EQUAL(outputStream2.str(), INVALIDBOOKMARK);

  std::istringstream stream3;
  std::ostringstream outputStream3;
  stream3.str(commandDelete);
  command = parse(stream3);
  BOOST_CHECK_NO_THROW(command(interface, outputStream3));

  std::istringstream stream4;
  std::ostringstream outputStream4;
  stream4.str(commandDelete);
  command = parse(stream4);
  command(emptyInterface, outputStream4);
  BOOST_CHECK_EQUAL(outputStream4.str(), EMPTY);
}

BOOST_FIXTURE_TEST_CASE(test_show, Fixture)
{
  std::istringstream stream;
  std::ostringstream outputStream;
  stream.str(invalidCommandShow1);
  CommandName command = parse(stream);
  command(interface, outputStream);
  BOOST_CHECK_EQUAL(outputStream.str(), INVALIDCOMMAND);

  std::istringstream stream2;
  std::ostringstream outputStream2;
  stream2.str(invalidCommandShow2);
  command = parse(stream2);
  command(interface, outputStream2);
  BOOST_CHECK_EQUAL(outputStream2.str(), INVALIDBOOKMARK);

  std::istringstream stream3;
  std::ostringstream outputStream3;
  stream3.str(commandShow);
  command = parse(stream3);
  BOOST_CHECK_NO_THROW(command(interface, outputStream3));

  std::istringstream stream4;
  std::ostringstream outputStream4;
  stream4.str(commandShow);
  command = parse(stream4);
  command(emptyInterface, outputStream4);
  BOOST_CHECK_EQUAL(outputStream4.str(), EMPTY);
}

BOOST_FIXTURE_TEST_CASE(test_move, Fixture)
{
  std::istringstream stream;
  std::ostringstream outputStream;
  stream.str(invalidCommandMove1);
  CommandName command = parse(stream);
  command(interface, outputStream);
  BOOST_CHECK_EQUAL(outputStream.str(), INVALIDCOMMAND);

  std::istringstream stream2;
  std::ostringstream outputStream2;
  stream2.str(invalidCommandMove2);
  BOOST_CHECK_THROW(parse(stream2), std::runtime_error);

  std::istringstream stream3;
  std::ostringstream outputStream3;
  stream3.str(invalidCommandMove3);
  command = parse(stream3);
  command(interface, outputStream3);
  BOOST_CHECK_EQUAL(outputStream3.str(), INVALIDBOOKMARK);

  std::istringstream stream4;
  std::ostringstream outputStream4;
  stream4.str(invalidCommandMove4);
  command = parse(stream4);
  command(interface, outputStream4);
  BOOST_CHECK_EQUAL(outputStream4.str(), INVALIDBOOKMARK);

  std::istringstream stream5;
  std::ostringstream outputStream5;
  stream5.str(invalidCommandMove5);
  command = parse(stream5);
  command(interface, outputStream5);
  BOOST_CHECK_EQUAL(outputStream5.str(), INVALIDBOOKMARK);

  std::istringstream stream6;
  std::ostringstream outputStream6;
  stream6.str(invalidCommandMove6);
  command = parse(stream6);
  BOOST_CHECK_NO_THROW(command(interface, outputStream6));

  std::istringstream stream7;
  std::ostringstream outputStream7;
  stream7.str(commandMove1);
  command = parse(stream7);
  BOOST_CHECK_NO_THROW(command(interface, outputStream7));

  std::istringstream stream8;
  std::ostringstream outputStream8;
  stream8.str(commandMove2);
  command = parse(stream8);
  BOOST_CHECK_NO_THROW(command(interface, outputStream8));

  std::istringstream stream9;
  std::ostringstream outputStream9;
  stream9.str(commandMove3);
  command = parse(stream9);
  BOOST_CHECK_NO_THROW(command(interface, outputStream9));

  std::istringstream stream10;
  std::ostringstream outputStream10;
  stream10.str(commandMove4);
  command = parse(stream10);
  BOOST_CHECK_NO_THROW(command(interface, outputStream10));
}

BOOST_AUTO_TEST_SUITE_END()
