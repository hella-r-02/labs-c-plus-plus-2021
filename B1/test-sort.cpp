#include <algorithm>
#include <stdexcept>

#include <vector>
#include <list>

#include <boost/test/unit_test.hpp>

#include "sort.hpp"
#include "detail.hpp"

BOOST_AUTO_TEST_SUITE(test_sort)
const int SIZE = 7;
auto comparatorAscending = determineOrder<int>("ascending");
auto comparatorDescending = determineOrder<int>("descending");

struct Fixture
{
  Fixture() :
  vector({4, 2, 1, 4, 8, -2, -6}),
  list({2, 1, -5, -8, 4, 8, 2}),
  sortAscendingVector(vector),
  sortAscendingList(list)
  {
    std::sort(sortAscendingVector.begin(), sortAscendingVector.end());
    sortDescendingVector = sortAscendingVector;
    std::reverse(sortDescendingVector.begin(), sortDescendingVector.end());
    sortAscendingList.sort();
    sortDescendingList = sortAscendingList;
    sortDescendingList.reverse();
  }

  std::vector<int> vector;
  std::list<int> list;
  std::vector<int> sortAscendingVector;
  std::list<int> sortAscendingList;
  std::vector<int> sortDescendingVector;
  std::list<int> sortDescendingList;
};

BOOST_FIXTURE_TEST_CASE(sort_with_operator, Fixture)
{
  sort<AccessByOperator>(vector, comparatorAscending);
  BOOST_CHECK_EQUAL(vector.size(), SIZE);
  BOOST_CHECK(vector == sortAscendingVector);
  sort<AccessByOperator>(vector, comparatorDescending);
  BOOST_CHECK_EQUAL(vector.size(), SIZE);
  BOOST_CHECK(vector == sortDescendingVector);

}

BOOST_FIXTURE_TEST_CASE(sort_with_at, Fixture)
{
  sort<AccessByAt>(vector, comparatorAscending);
  BOOST_CHECK_EQUAL(vector.size(), SIZE);
  BOOST_CHECK(vector == sortAscendingVector);
  sort<AccessByAt>(vector, comparatorDescending);
  BOOST_CHECK_EQUAL(vector.size(), SIZE);
  BOOST_CHECK(vector == sortDescendingVector);
}

BOOST_FIXTURE_TEST_CASE(sort_with_iterator, Fixture)
{
  sort<AccessByIterator>(vector, comparatorAscending);
  BOOST_CHECK_EQUAL(vector.size(), SIZE);
  BOOST_CHECK(vector == sortAscendingVector);
  sort<AccessByIterator>(vector, comparatorDescending);
  BOOST_CHECK_EQUAL(vector.size(), SIZE);
  BOOST_CHECK(vector == sortDescendingVector);
}

BOOST_AUTO_TEST_CASE(comp)
{
  auto comparator = determineOrder<double>("ascending");
  BOOST_CHECK(comparator(1, 2) == false);
  BOOST_CHECK(comparator(2, 1) == true);
  comparator = determineOrder<double>("descending");
  BOOST_CHECK(comparator(1, 2) == true);
  BOOST_CHECK(comparator(2, 1) == false);
  BOOST_CHECK_THROW(determineOrder<double>(nullptr), std::invalid_argument);
  BOOST_CHECK_THROW(determineOrder<double>("des"), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()
