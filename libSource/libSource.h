#pragma once

#include <string>
#include <vector> 

#define REGEX_CONST "^((25[0-5]|2[0-4][\\d]|1[\\d][\\d]|[\\d]?[\\d])[\\.,\\s]){3}(25[0-5]|2[0-4][\\d]|1[\\d][\\d]|[\\d]?[\\d])$"


namespace libSource
{
    using vectVectStr = std::vector<std::vector<std::string>>;
    using vectVectInt = std::vector<std::vector<int>>;
    using vectStr     = std::vector<std::string>;
    using vectInt     = std::vector<int>;

    vectStr setListOfFilesInVector(int &argc, char **argv);
    
    void checkFilesForOpenAndFillMainContent(vectStr const & bufferOfFilesNames, std::string & mainContent);

    void writeInFile(const vectVectInt & ipInFile);
    vectVectInt& concatenateIp(vectVectInt &basicIp,vectVectInt &ip);
    
    vectStr split(std::string const & str, char symbol);
    bool lexiCompare(const vectInt &a, const vectInt &b);
    void sortIp(vectVectInt & ip);
    void show(vectVectStr & ipList);
    void show(vectVectInt & ipList);
    vectVectInt filter_any(vectVectInt & vInside, int param);

    template<typename ... Args>
    vectVectInt filter(vectVectInt & ipBytes, const Args ... args);

    void checkForTrash(vectStr & ipForCheck);
    vectVectInt convertToInt(const vectVectStr &ipSorted);

    vectVectInt prepareIpContainer(const vectStr &rows);
}; 

#include "filters.tpp"


