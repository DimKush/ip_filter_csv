#include <string>
#include <iostream>
#include <exception>
#include <algorithm>

#include "libSource.h"
#include "libUnitTest.h"
#include "../version.h"

using namespace libSource;


namespace libUnitTest
{
    int returnVersion()
    {
        return PROJECT_VERSION_PATCH;
    }

    int isRegexpValueCorrect()
    {
        const std::string regexIpVal("^((25[0-5]|2[0-4][\\d]|1[\\d][\\d]|[\\d]?[\\d])[\\.,\\s]){3}(25[0-5]|2[0-4][\\d]|1[\\d][\\d]|[\\d]?[\\d])$");
        
        return regexIpVal.compare(REGEX_CONST);
    }

    ERROR_TYPES checkRowsContainer(const char * val)
    {
        std::string content = std::string(val); 
        vectStr rows;

        try
        {
            rows = split(content, '\n');
            
            for(size_t i = 0 ; i < rows.size() ; i++)
            {
                rows.at(i) = split(rows.at(i),';').at(0);
            }

            std::for_each(rows.begin(), rows.end(), [](const std::string & element)
            {
                 throw element.empty();
            });

           
        }
        catch(const bool isRowsEmpty)
        {
            if(isRowsEmpty)
                return ERROR_TYPES::EMPTY_ROWS_CONTAINER;
        }

        return ERROR_TYPES::GOOD;
    }
};