#include "libSource.h"
#include <iostream>

using namespace libSource;

int main(int argc, char **argv)
{    
    
	std::string mainContent;
    vectStr rows, ListOfFilesInVector;
    vectVectStr ipBytesStr;
    vectVectInt ip, filtredIpOne, filtredIpTwo, filtredIpThree;
  
    ListOfFilesInVector = setListOfFilesInVector(argc,argv);
    checkFilesForOpenAndFillMainContent(ListOfFilesInVector, mainContent);
    
    rows = split(mainContent, '\n');
    
    ip = prepareIpContainer(rows);
 
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
