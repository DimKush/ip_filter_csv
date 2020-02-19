#define BOOST_TEST_MODULE ip_filter_test_module

#include "../libUnitTest/libUnitTest.h"
#include <boost/test/included/unit_test.hpp>

#define TEST_DATA "113.162.145.156;111;0\n \
                   157.39.22.224;5;6\n     \
                   79.180.73.190;2;1\n     \
                   179.210.145.4;22;0\n"

#define TEST_DATA_INCORRECT "1100.1622.1345.1156;1211;440,44;422,44\n \
                             157.39.22.224;5;6\n     \
                             7900.1820.734.19110;23;144.sfsdgdgfdgfdgfdgd\n     \
                             17922.23310.1145.43;2442;10,/';sdfsdfsfsfwe2423\n"
                             
#define TEST_DATA_NONSENCE "Sfsdgdgdggdfgddgdfgdgertetergfdgdfgedrtefgdertetrtreert"

#define TEST_DATA_EMPTY ""

BOOST_AUTO_TEST_SUITE(ip_filter_test_module_suite)

BOOST_AUTO_TEST_CASE(ip_filter_test_version)
{
    BOOST_CHECK(libUnitTest::returnVersion() > 0);
}

BOOST_AUTO_TEST_CASE(ip_filter_test_regex)
{
    BOOST_CHECK(libUnitTest::isRegexpValueCorrect() == 0);
}

BOOST_AUTO_TEST_CASE(ip_filter_test_rows)
{
    BOOST_CHECK(libUnitTest::checkRowsContainer(TEST_DATA) == libUnitTest::ERROR_TYPES::GOOD);
    BOOST_CHECK(libUnitTest::checkRowsContainer(TEST_DATA_INCORRECT) == libUnitTest::ERROR_TYPES::GOOD);
    BOOST_CHECK(libUnitTest::checkRowsContainer(TEST_DATA_NONSENCE) == libUnitTest::ERROR_TYPES::GOOD);
    BOOST_CHECK(libUnitTest::checkRowsContainer(TEST_DATA_EMPTY) == libUnitTest::ERROR_TYPES::EMPTY_ROWS_CONTAINER);
    
}

BOOST_AUTO_TEST_SUITE_END()