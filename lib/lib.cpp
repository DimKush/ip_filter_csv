#include "lib.h"
#include "../version.h"
#include <string>
#include <iostream>

int returnVersion()
{
    return PROJECT_VERSION_PATCH;
}

int isRegexpValueCorrect()
{
    const std::string regexIpVal("^((25[0-5]|2[0-4][\\d]|1[\\d][\\d]|[\\d]?[\\d])[\\.,\\s]){3}(25[0-5]|2[0-4][\\d]|1[\\d][\\d]|[\\d]?[\\d])$");
    
    return regexIpVal.compare(REGEX_CONST);
}