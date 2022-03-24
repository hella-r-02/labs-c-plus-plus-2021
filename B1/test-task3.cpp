#include <iostream>
#include <stdexcept>
#include <cstring>

#include <boost/test/unit_test.hpp>

#include "tasks.hpp"

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

BOOST_AUTO_TEST_SUITE(test_task3)

BOOST_FIXTURE_TEST_CASE(invalid_data, Fixture)
{
  const std::string input = "a 10 1 0\n";
  in.str(input);
  std::cout.rdbuf(coutbuf);
  BOOST_CHECK_THROW(taskThree(), std::invalid_argument);
}

BOOST_FIXTURE_TEST_CASE(last_number_1, Fixture)
{
  const std::string input = "1 2 4 7 8 10 2 1 0";
  in.str(input);
  taskThree();
  const std::string output = out.str();
  const std::string correctOutput = "1 7 1 ";
  redirection();
  BOOST_CHECK_EQUAL(output, correctOutput);
}

BOOST_FIXTURE_TEST_CASE(last_number_2, Fixture)
{
  const std::string input = "3 6 1 2 3 9 2 0";
  in.str(input);
  taskThree();
  const std::string output = out.str();
  const std::string correctOutput = "3 1 1 1 6 1 1 1 1 2 3 1 1 1 9 1 1 1 2 ";
  redirection();
  BOOST_CHECK_EQUAL(output, correctOutput);
}

BOOST_FIXTURE_TEST_CASE(last_number_not_1_not_2, Fixture)
{
  const std::string input = "3 6 1 2 3 9 3 0";
  in.str(input);
  taskThree();
  const std::string output = out.str();
  const std::string correctOutput = "3 6 1 2 3 9 3 ";
  redirection();
  BOOST_CHECK_EQUAL(output, correctOutput);
}

BOOST_AUTO_TEST_SUITE_END()
