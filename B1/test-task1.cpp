#include <iostream>
#include <stdexcept>
#include <cstring>

#include <boost/test/unit_test.hpp>

#include "tasks.hpp"
#include "detail.hpp"

struct Fixture
{
  Fixture() :

    cinbuf(std::cin.rdbuf(in.rdbuf())),
    coutbuf(std::cout.rdbuf(out.rdbuf()))
  {}

  void redirection()
  {
    std::cin.rdbuf(cinbuf);
    std::cout.rdbuf(coutbuf);
  }
  std::streambuf *cinbuf;
  std::streambuf *coutbuf;
  std::istringstream in;
  std::ostringstream out;
};

BOOST_AUTO_TEST_SUITE(test_task1)

BOOST_AUTO_TEST_CASE(invalid_argument_cmp)
{
  BOOST_CHECK_THROW(taskOne(determineOrder<int>("not order")), std::invalid_argument);
}

BOOST_FIXTURE_TEST_CASE(invalid_data, Fixture)
{

  const std::string input = "a 10 1 \n";
  in.str(input);
  std::cout.rdbuf(coutbuf);
  auto comparator = determineOrder<int>("ascending");
  BOOST_CHECK_THROW(taskOne(comparator), std::invalid_argument);
  const std::string input2 = "";
  in.str(input2);
  std::cout.rdbuf(coutbuf);
  comparator = determineOrder<int>("descending");
  BOOST_CHECK_THROW(taskOne(comparator), std::invalid_argument);
}

BOOST_FIXTURE_TEST_CASE(test_ascending, Fixture)
{
  const std::string input = "9 10 1 -1\n";
  in.str(input);
  auto comparator = determineOrder<int>("ascending");
  taskOne(comparator);
  const std::string output = out.str();
  const std::string correctOutput = "-1 1 9 10 \n-1 1 9 10 \n-1 1 9 10 ";
  redirection();
  BOOST_CHECK_EQUAL(output, correctOutput);
}

BOOST_FIXTURE_TEST_CASE(test_descending, Fixture)
{
  const std::string input = "3 4 8 2\n";
  in.str(input);
  auto comparator = determineOrder<int>("descending");
  taskOne(comparator);
  const std::string output = out.str();
  const std::string correctOutput = "8 4 3 2 \n8 4 3 2 \n8 4 3 2 ";
  redirection();
  BOOST_CHECK_EQUAL(output, correctOutput);
}

BOOST_AUTO_TEST_SUITE_END()
