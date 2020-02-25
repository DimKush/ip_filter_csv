#include "libSource.h"

using namespace libSource;

int main(int argc, char **argv)
{
    std::string mainContent;
    vectStr rows, ListOfFilesInVector;
    vectVectStr ipBytesStr;
    vectVectInt ip, filtredIpOne, filtredIpTwo, filtredIpThree;

    
    checkFilesForOpenAndFillMainContent(setListOfFilesInVector(argc,argv), mainContent);

    rows = split(mainContent, '\n');
    
    for(size_t i = 0 ; i < rows.size() ; i++)
    {
        rows.at(i) = split(rows.at(i),';').at(0);
    }
    
    checkForTrash(rows);

    for(size_t i = 0 ; i < rows.size() ; i++)
    {
        ipBytesStr.push_back(split(rows.at(i), '.'));
    }

    ip = convertToInt(ipBytesStr); 
    
    sortIp(ip);
    
    filtredIpOne = filter(ip, 1);

    filtredIpTwo = filter(ip, 46,70); 

    filtredIpThree = filter_any(ip, 46);

    concatenateIp(ip, filtredIpOne);
    concatenateIp(ip, filtredIpTwo);
    concatenateIp(ip, filtredIpThree);

    writeInFile(ip);
    
    return 0;
}