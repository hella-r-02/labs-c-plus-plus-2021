#include <iostream>
#include <stdexcept>
#include <cstring>
#include <vector>

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

BOOST_AUTO_TEST_SUITE(test_task4)

auto comparatorDescending = determineOrder<double>("descending");
const int SIZE = 10;

BOOST_AUTO_TEST_CASE(invalid_size)
{
  BOOST_CHECK_THROW(taskFour(comparatorDescending, 0), std::invalid_argument);
  BOOST_CHECK_THROW(taskFour(comparatorDescending, -1), std::length_error);
}

BOOST_FIXTURE_TEST_CASE(test_task_four_descending, Fixture)
{
  taskFour(comparatorDescending, 5);
  const std::string output = out.str();
  redirection();
  size_t pos = 0;
  pos = output.find("\n");
  BOOST_CHECK(pos != 0);
  std::string sortString = output.substr(pos + 1);
  const char *cSortString = sortString.c_str();
  double firstNumber = std::strtod(cSortString, 0);
  double lastNumber = std::strtod(cSortString, NULL);

  BOOST_REQUIRE(lastNumber >= -1);
  BOOST_REQUIRE(firstNumber <= 1);
}

BOOST_AUTO_TEST_CASE(test_fillRandom)
{
  std::vector<double> vector(SIZE, 0);
  fillRandom(&vector[0], SIZE);
  BOOST_CHECK_EQUAL(vector.size(), SIZE);
  for (int i = 0; i < SIZE; i++)
  {
    BOOST_CHECK(vector[i] <= 1 && vector[i] >= -1);
  }
}

BOOST_AUTO_TEST_SUITE_END()
