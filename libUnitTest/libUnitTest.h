#pragma once

namespace libUnitTest
{
    enum class ERROR_TYPES : int
    {
        EMPTY_ROWS_CONTAINER, GOOD
    };

    int returnVersion();
    int isRegexpValueCorrect();
    ERROR_TYPES checkRowsContainer(const char * val);

}