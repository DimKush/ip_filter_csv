#include "libUnitTest.h"
#include "../version.h"
#include "libSource.h"
#include <gtest/gtest.h>
#include <fstream>
#include <cstring>
 

using namespace libSource;

namespace UnitTests
{   
    std::string globContentFrmFiles;
    vectStr listOfFiles, unitTestFileContent, expectedFromTestFile, unitTestFileSecondContent, expectedAfterSplit, expectedAfterCheckForTrash; 

    void prepareData()
    {
        //first file
        unitTestFileContent.emplace_back(std::string("113.162.145.156;111;0"));
        unitTestFileContent.emplace_back(std::string("157.39.22.224;5;6"));
        unitTestFileContent.emplace_back(std::string("afsfsdfwr23r2323r"));
        unitTestFileContent.emplace_back(std::string("1790.2101.1453.554;22;0"));
        unitTestFileContent.emplace_back(std::string("113.162.145.156;111;0"));
        unitTestFileContent.emplace_back(std::string("157.1.222.234;5;6"));
        unitTestFileContent.emplace_back(std::string("157.84.232.134;5;6"));
        unitTestFileContent.emplace_back(std::string("\n"));
        
        //second file
        unitTestFileSecondContent.emplace_back(std::string("1790.2101.1453.554;22;0"));
        unitTestFileSecondContent.emplace_back(std::string("113.162.145.156;111;0"));

        expectedFromTestFile = unitTestFileContent;
        expectedFromTestFile.insert(expectedFromTestFile.end(), unitTestFileSecondContent.begin(), unitTestFileSecondContent.end());

        expectedAfterSplit.emplace_back(std::string("113.162.145.156"));
        expectedAfterSplit.emplace_back(std::string("157.39.22.224"));
        expectedAfterSplit.emplace_back(std::string("afsfsdfwr23r2323r"));
        expectedAfterSplit.emplace_back(std::string("1790.2101.1453.554"));
        expectedAfterSplit.emplace_back(std::string("113.162.145.156"));
        expectedAfterSplit.emplace_back(std::string("157.1.222.234"));
        expectedAfterSplit.emplace_back(std::string("157.84.232.134"));
        expectedAfterSplit.emplace_back(std::string("\n"));
        expectedAfterSplit.emplace_back(std::string("1790.2101.1453.554"));
        expectedAfterSplit.emplace_back(std::string("113.162.145.156"));


        expectedAfterCheckForTrash.emplace_back(std::string("113.162.145.156"));
        expectedAfterCheckForTrash.emplace_back(std::string("157.39.22.224"));
        expectedAfterCheckForTrash.emplace_back(std::string("113.162.145.156"));
        expectedAfterCheckForTrash.emplace_back(std::string("157.1.222.234"));
        expectedAfterCheckForTrash.emplace_back(std::string("157.84.232.134"));

        // list of files
        listOfFiles.emplace_back("unitTestFile.csv");
        listOfFiles.emplace_back("unitTestFileSecond.csv");
    }
    
    void createTestFile()
    {
        std::ofstream file("unitTestFile.csv");

        for(auto ip = unitTestFileContent.cbegin(); ip != unitTestFileContent.cend(); ++ip)
        {
            file << *ip << "\n";
            globContentFrmFiles += *ip + "\n" ;
        }

        std::ofstream fileSecond("unitTestFileSecond.csv");

        for(auto ip = unitTestFileSecondContent.cbegin(); ip != unitTestFileSecondContent.cend(); ++ip)
        {
            file << *ip << "\n";
            globContentFrmFiles += *ip + "\n" ;
        }
    }

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
 
TEST(openAndPrepareContentFromFile, fillBufferOfFilenamesTest)
{
    UnitTests::prepareData();
    UnitTests::createTestFile();
    vectStr sample;
    
    if(globArgc == 1) // if unit test was ranning without arguments
    {
        globArgc = 3;
        globArgv[1] = new char[UnitTests::listOfFiles.at(0).size()];
        globArgv[2] = new char[UnitTests::listOfFiles.at(1).size()];

        strcpy(globArgv[1],UnitTests::listOfFiles.at(0).c_str());
        strcpy(globArgv[2],UnitTests::listOfFiles.at(1).c_str());

        for(int i = 0 ; i < globArgc; i++)
        std::cout << globArgv[i] << std::endl;
    }
    
    sample = setListOfFilesInVector(globArgc, globArgv);

    for( auto i : sample)
    {
        std::cout << "sample element : " << i << "\n";
    }

    ASSERT_TRUE(!sample.empty());
    ASSERT_EQ(globArgc - 1, sample.size()); // - 1 because first(0) calling in argc is the calling of program  
    
    UnitTests::listOfFiles = sample;
};


TEST(openAndPrepareContentFromFile, fillContentFromfileTest)
{
    std::string content;

    checkFilesForOpenAndFillMainContent(UnitTests::listOfFiles, content);
    std::cout << content;
    ASSERT_TRUE(!content.empty());
}; 


TEST(splitAndCheckForTrash, PrepareInformationTest)
{
    std::vector<std::string> factFromTestFile(split(UnitTests::globContentFrmFiles,'\n'));

    ASSERT_TRUE(std::equal(UnitTests::expectedFromTestFile.begin(),UnitTests::expectedFromTestFile.end()
                          ,factFromTestFile.begin(),factFromTestFile.end()));

    for(size_t i = 0 ; i < factFromTestFile.size() ; i++)
    {
        factFromTestFile.at(i) = split(factFromTestFile.at(i),';').at(0);
    }

    ASSERT_TRUE(std::equal(UnitTests::expectedAfterSplit.begin(),UnitTests::expectedAfterSplit.end()
                          ,factFromTestFile.begin(),factFromTestFile.end()));
    
    checkForTrash(factFromTestFile);
    
    ASSERT_TRUE(std::equal(UnitTests::expectedAfterCheckForTrash.begin(),UnitTests::expectedAfterCheckForTrash.end()
                          ,factFromTestFile.begin(),factFromTestFile.end()));
};
