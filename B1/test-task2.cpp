#include <iostream>
#include <fstream>
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

BOOST_AUTO_TEST_SUITE(test_task2)

BOOST_AUTO_TEST_CASE(invalid_file_name)
{
  BOOST_CHECK_THROW(taskTwo("file"), std::runtime_error);
}

BOOST_FIXTURE_TEST_CASE(correct_argument, Fixture)
{
  const char *filename = "test.txt";
  std::ofstream outStream;
  outStream.open(filename);
  outStream << "1 a 2 3" << std::endl;
  taskTwo(filename);
  const std::string output = out.str();
  redirection();
  const std::string correctOutput = "1 a 2 3\n";
  BOOST_CHECK_EQUAL(output, correctOutput);
}

BOOST_AUTO_TEST_SUITE_END()
