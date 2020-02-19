#define BOOST_TEST_MODULE ip_filter_test_module

#include "../lib/lib.h"
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(ip_filter_test_module_suite)

BOOST_AUTO_TEST_CASE(ip_filter_test_version)
{
    BOOST_CHECK(returnVersion() > 0);
}

BOOST_AUTO_TEST_CASE(ip_filter_test_regex)
{
    BOOST_CHECK(isRegexpValueCorrect() == 0);
}
BOOST_AUTO_TEST_SUITE_END()