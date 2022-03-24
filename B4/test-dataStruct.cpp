#include<stdexcept>

#include <boost/test/unit_test.hpp>

#include "dataStruct.hpp"


BOOST_AUTO_TEST_SUITE(test_task)

BOOST_AUTO_TEST_CASE(test_task)
{
  std::istringstream stream;
  std::ostringstream outputStream;

  stream.str("1,2,qow\n1,2,drtes");
  task(stream, outputStream);
  BOOST_CHECK_EQUAL(outputStream.str(), "1,2,qow\n1,2,drtes\n");
}
BOOST_AUTO_TEST_SUITE_END()
