#include<stdexcept>

#include <boost/test/unit_test.hpp>

#include "utility.hpp"

BOOST_AUTO_TEST_SUITE(test_separator)

BOOST_AUTO_TEST_CASE(test_read_separator)
{
  Separator separator;
  std::istringstream stream;
  stream.str(",");
  stream >> separator;
  BOOST_CHECK(stream);

  Separator separator2;
  std::istringstream stream2;
  stream2.str(":");
  stream2 >> separator2;
  BOOST_CHECK(!stream2);
}

BOOST_AUTO_TEST_SUITE_END()
