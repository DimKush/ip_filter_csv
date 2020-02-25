#include "libUnitTest.h"
#include "../version.h"
#include "libSource.h"
#include <gtest/gtest.h>

using namespace libSource;

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
    ASSERT_TRUE(UnitTests::checkBuildVersion());
};
TEST(checkRegexp, regexpController)
{
    ASSERT_EQ(0, UnitTests::checkRegexp());
};

TEST(openAndPrepareFile, Controller)
{
    vectStr sample = setListOfFilesInVector(globArgc, globArgv);

    for( auto i : sample)
    {
        std::cout << "sample element : " << i << "\n";
    }

    ASSERT_EQ(false, sample.empty());
    ASSERT_EQ(globArgc - 1, sample.size()); // - 1 because first(0) calling in argc is the calling of program 
};