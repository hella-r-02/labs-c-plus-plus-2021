#include <stdexcept>

#include <boost/test/unit_test.hpp>

#include "factorialContainer.hpp"

FactorialContainer factorialContainer(10);
FactorialContainer emptyFactorialContainer;

BOOST_AUTO_TEST_SUITE(test_factorial_container)

BOOST_AUTO_TEST_CASE(test_begin_and_end)
{
  auto it = factorialContainer.begin();
  BOOST_CHECK_EQUAL(*it, 1);

  it = factorialContainer.end();
  BOOST_CHECK_EQUAL(*it, 1 * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10 * 11);

  it = emptyFactorialContainer.begin();
  BOOST_CHECK_EQUAL(*it, 1);
  it = emptyFactorialContainer.end();
  BOOST_CHECK_EQUAL(*it, 1);
}

BOOST_AUTO_TEST_CASE(test_rbegin_and_rend)
{
  auto it = factorialContainer.rend();
  BOOST_CHECK_EQUAL(*it, 1);

  it = factorialContainer.rbegin();
  BOOST_CHECK_EQUAL(*it, 1 * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10);

  it = emptyFactorialContainer.rbegin();
  BOOST_CHECK_EQUAL(*it, 1);
  it = emptyFactorialContainer.rend();
  BOOST_CHECK_EQUAL(*it, 1);
}

BOOST_AUTO_TEST_CASE(test_increment_and_decrement_and_comparison_operator)
{
  FactorialContainer container(1);
  auto itBegin = container.begin();
  auto itEnd = container.end();
  auto tempIt = itBegin;

  BOOST_CHECK(tempIt == itBegin);
  BOOST_CHECK(tempIt != itEnd);

  tempIt++;
  BOOST_CHECK(tempIt == itEnd);
  BOOST_CHECK(tempIt != itBegin);

  tempIt--;
  BOOST_CHECK(tempIt == itBegin);
  BOOST_CHECK(tempIt != itEnd);

  tempIt--;
  BOOST_CHECK_THROW(tempIt--, std::out_of_range);

  tempIt = emptyFactorialContainer.begin();
  tempIt--;
  BOOST_CHECK_THROW(tempIt--, std::out_of_range);

}

BOOST_AUTO_TEST_CASE(test_check_value_iterator)
{
  auto it = factorialContainer.begin();
  size_t value = 1;
  for (size_t i = 2; i <= 10; i++)
  {
    BOOST_CHECK_EQUAL(*it, value);
    value *= i;
    it++;
  }
}

BOOST_AUTO_TEST_CASE(test_container_overflow)
{
  BOOST_CHECK_THROW(FactorialContainer factorialContainer2(20), std::overflow_error);
}

BOOST_AUTO_TEST_SUITE_END()
