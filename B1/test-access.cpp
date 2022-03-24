#include <stdexcept>

#include <vector>
#include <list>

#include <boost/test/unit_test.hpp>

#include "access.hpp"

BOOST_AUTO_TEST_SUITE(test_access)
const int SIZE = 7;
struct Fixture
{
  Fixture() :
    vector({4, 2, 4, 1, 8, -2, -6}),
    list({2, 1, -5, -8, 4, 8, 2})
  {}
  std::vector<int> vector;
  std::list<int> list;

};

BOOST_FIXTURE_TEST_CASE(invalid_argunemt, Fixture)
{
  BOOST_CHECK_THROW(AccessByAt<std::vector<int>>::getElement(vector, -1), std::out_of_range);
}

BOOST_FIXTURE_TEST_CASE(test_AccessByOperator, Fixture)
{
  BOOST_CHECK(0 == AccessByOperator<std::vector<int>>::getBegin(vector));
  BOOST_CHECK(SIZE == AccessByOperator<std::vector<int>>::getEnd(vector));
  for (int i = 0; i < SIZE; i++)
  {
    BOOST_CHECK(vector[i] == AccessByOperator<std::vector<int>>::getElement(vector, i));
  }
}

BOOST_FIXTURE_TEST_CASE(test_AccessByAt, Fixture)
{
  BOOST_CHECK(0 == AccessByAt<std::vector<int>>::getBegin(vector));
  BOOST_CHECK(SIZE == AccessByAt<std::vector<int>>::getEnd(vector));
  for (int i = 0; i < SIZE; i++)
  {
    BOOST_CHECK(vector.at(i) == AccessByAt<std::vector<int>>::getElement(vector, i));
  }
}

BOOST_FIXTURE_TEST_CASE(test_AccessByIterator, Fixture)
{
  BOOST_CHECK(list.begin() == AccessByIterator<std::list<int>>::getBegin(list));
  BOOST_CHECK(list.end() == AccessByIterator<std::list<int>>::getEnd(list));
  std::list<int>::iterator i;

  for (i = list.begin(); i != list.end(); i++)
  {
    BOOST_CHECK(*i == AccessByIterator<std::list<int>>::getElement(list, i));
  }
}

BOOST_AUTO_TEST_SUITE_END()
