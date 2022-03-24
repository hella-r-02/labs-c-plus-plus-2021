#include<stdexcept>

#include <boost/test/unit_test.hpp>

#include "data-struct.hpp"

BOOST_AUTO_TEST_SUITE(test_data_struct)

BOOST_AUTO_TEST_CASE(test_correct_read_data_struct)
{
  std::istringstream stream;
  DataStruct data_struct1;
  stream.str("1,2,lal");
  stream >> data_struct1;
  BOOST_CHECK(stream);

  std::istringstream stream2;
  DataStruct data_struct2;
  stream2.str("-1,2,lal");
  stream2 >> data_struct2;
  BOOST_CHECK(stream2);

  std::istringstream stream3;
  DataStruct data_struct3;
  stream3.str("1,-2,lal");
  stream3 >> data_struct3;
  BOOST_CHECK(stream3);

  std::istringstream stream4;
  DataStruct data_struct4;
  stream4.str("-1,-2,lal");
  stream4 >> data_struct4;
  BOOST_CHECK(stream4);
}

BOOST_AUTO_TEST_CASE(test_uncorrect_read_data_struct)
{
  std::istringstream stream;
  DataStruct data_struct1;
  stream.str("10,2,lal");
  stream >> data_struct1;
  BOOST_CHECK(!stream);

  std::istringstream stream2;
  DataStruct data_struct2;
  stream2.str("-1,23,lal");
  stream2 >> data_struct2;
  BOOST_CHECK(!stream2);

  std::istringstream stream3;
  DataStruct data_struct3;
  stream3.str("1\n,-2,lal");
  stream3 >> data_struct3;
  BOOST_CHECK(!stream3);

  std::istringstream stream4;
  DataStruct data_struct4;
  stream4.str("-1,\n-2,lal");
  stream4 >> data_struct4;
  BOOST_CHECK(!stream4);

  std::istringstream stream5;
  DataStruct data_struct5;
  stream5.str("-1,-2\n,lal");
  stream5 >> data_struct5;
  BOOST_CHECK(!stream5);

  std::istringstream stream6;
  DataStruct data_struct6;
  stream6.str("-1,-2,\nlal");
  stream6 >> data_struct6;
  BOOST_CHECK(!stream6);

  std::istringstream stream7;
  DataStruct data_struct7;
  stream7.str("-1,-2,\nlal");
  stream7 >> data_struct7;
  BOOST_CHECK(!stream7);
}
BOOST_AUTO_TEST_CASE(test_comparison_data_struct)
{
  Comparator comparator;
  DataStruct data_struct1 = {1, 2, "kql"};
  DataStruct data_struct2 = {2, 2, "kql"};
  BOOST_CHECK(comparator(data_struct1, data_struct2));

  DataStruct data_struct3 = {2, 4, "kql"};
  DataStruct data_struct4 = {2, 2, "kql"};
  BOOST_CHECK(!comparator(data_struct3, data_struct4));

  DataStruct data_struct5 = {2, 4, "kql"};
  DataStruct data_struct6 = {2, 4, "kqlxzakls"};
  BOOST_CHECK(comparator(data_struct5, data_struct6));
}
BOOST_AUTO_TEST_SUITE_END()
