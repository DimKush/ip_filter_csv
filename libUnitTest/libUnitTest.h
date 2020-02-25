#pragma once
#include "libUnitTest.h"
#include "../version.h"

extern int globArgc; 
extern char **globArgv;

namespace UnitTests
{
    bool checkBuildVersion();
    int checkRegexp();
};