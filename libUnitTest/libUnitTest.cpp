#include "libUnitTest.h"
#include "../version.h"
#include "libSource.h"
#include <gtest/gtest.h>


namespace UnitTests
{
    bool checkBuildVersion()
    {
        return PROJECT_VERSION_PATCH > 0;
    }

    int checkRegexp()
    {
       std::string constRegexp("^((25[0-5]|2[0-4][\\d]|1[\\d][\\d]|[\\d]?[\\d])[\\.,\\s]){3}(25[0-5]|2[0-4][\\d]|1[\\d][\\d]|[\\d]?[\\d])$");
       std::string currentRegexp(REGEX_CONST);

       return constRegexp.compare(currentRegexp);
    }
};

// unit tests
TEST(checkVersion, versionController)
{
    ASSERT_EQ(true, UnitTests::checkBuildVersion());
};
TEST(checkRegexp, regexpController)
{
    ASSERT_EQ(0, UnitTests::checkRegexp());
};
