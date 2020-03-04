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
    vectStr listOfFiles, unitTestFileContent, expectedFromTestFile, unitTestFileSecondContent, 
            expectedAfterSplit, expectedAfterCheckForTrash, expectedAfterControlСharSplit; 
    
    vectVectStr expectedAfterSplitBytes;
    vectVectInt expectedAfterConvering, expectedSortedContainer, expectedFiltredFirst, expectedFiltredSecond, expectedFiltredAny;

    template<typename T, typename ... Args>
    void  helpToFillContainer(std::vector<T> & container, const Args ... args)
    {
        container.clear();
        (container.emplace_back(args),...);
    }

    std::string finalStrBuilder(vectVectInt & doneTestFileContainer)
    {
        std::string prepareStr;

        for(auto ip = doneTestFileContainer.cbegin(); ip != doneTestFileContainer.cend(); ++ip)
        {
            for(auto ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
            {
                if (ip_part != ip->cbegin())
                {
                  prepareStr +=  '.';
                }
                prepareStr += std::to_string(*(ip_part));
            }
            prepareStr += '\n';
        }

        return prepareStr;
    }

    void prepareData()
    {
        //first file
        unitTestFileContent.emplace_back(std::string("113.162.145.156;111;0"));
        unitTestFileContent.emplace_back(std::string("157.39.22.224;5;6"));
        unitTestFileContent.emplace_back(std::string("afsfsdfwr23r2323r"));
        unitTestFileContent.emplace_back(std::string(""));
        unitTestFileContent.emplace_back(std::string("1790.2101.1453.554;22;0"));
        unitTestFileContent.emplace_back(std::string("113.162.145.156;111;0"));
        unitTestFileContent.emplace_back(std::string("157.1.222.234;5;6"));
        unitTestFileContent.emplace_back(std::string("157.84.232.134;5;6"));
        
        //second file
        unitTestFileSecondContent.emplace_back(std::string("1790.2101.1453.554;22;0"));
        unitTestFileSecondContent.emplace_back(std::string("113.162.145.156;111;0"));

        // string of content from file
        for(auto i : unitTestFileContent)
            globContentFrmFiles += i + '\n';
        
        for(auto i : unitTestFileSecondContent)
            globContentFrmFiles += i + '\n';
        
        // after split control character '\n' 
        expectedAfterControlСharSplit.emplace_back(std::string("113.162.145.156;111;0"));
        expectedAfterControlСharSplit.emplace_back(std::string("157.39.22.224;5;6"));
        expectedAfterControlСharSplit.emplace_back(std::string("afsfsdfwr23r2323r"));
        expectedAfterControlСharSplit.emplace_back(std::string(""));
        expectedAfterControlСharSplit.emplace_back(std::string("1790.2101.1453.554;22;0"));
        expectedAfterControlСharSplit.emplace_back(std::string("113.162.145.156;111;0"));
        expectedAfterControlСharSplit.emplace_back(std::string("157.1.222.234;5;6"));
        expectedAfterControlСharSplit.emplace_back(std::string("157.84.232.134;5;6"));
        expectedAfterControlСharSplit.emplace_back(std::string("1790.2101.1453.554;22;0"));
        expectedAfterControlСharSplit.emplace_back(std::string("113.162.145.156;111;0"));
        expectedAfterControlСharSplit.emplace_back(std::string(""));

        // after split container
        expectedAfterSplit.emplace_back(std::string("113.162.145.156"));
        expectedAfterSplit.emplace_back(std::string("157.39.22.224"));
        expectedAfterSplit.emplace_back(std::string("afsfsdfwr23r2323r"));
        expectedAfterSplit.emplace_back(std::string(""));
        expectedAfterSplit.emplace_back(std::string("1790.2101.1453.554"));
        expectedAfterSplit.emplace_back(std::string("113.162.145.156"));
        expectedAfterSplit.emplace_back(std::string("157.1.222.234"));
        expectedAfterSplit.emplace_back(std::string("157.84.232.134"));
        expectedAfterSplit.emplace_back(std::string("1790.2101.1453.554"));
        expectedAfterSplit.emplace_back(std::string("113.162.145.156"));
        expectedAfterSplit.emplace_back(std::string(""));

        expectedAfterCheckForTrash.emplace_back(std::string("113.162.145.156"));
        expectedAfterCheckForTrash.emplace_back(std::string("157.39.22.224"));
        expectedAfterCheckForTrash.emplace_back(std::string("113.162.145.156"));
        expectedAfterCheckForTrash.emplace_back(std::string("157.1.222.234"));
        expectedAfterCheckForTrash.emplace_back(std::string("157.84.232.134"));
        expectedAfterCheckForTrash.emplace_back(std::string("113.162.145.156"));

        // list of files
        listOfFiles.emplace_back("unitTestFile.csv");
        listOfFiles.emplace_back("unitTestFileSecond.csv");

        //expected after split by bytes
        std::vector<std::string> tmpContinerStr;
        helpToFillContainer(tmpContinerStr, "113","162","145","156");
            expectedAfterSplitBytes.emplace_back(tmpContinerStr);
        helpToFillContainer(tmpContinerStr, "157","39","22","224");
            expectedAfterSplitBytes.emplace_back(tmpContinerStr);
        helpToFillContainer(tmpContinerStr, "113","162","145","156");
            expectedAfterSplitBytes.emplace_back(tmpContinerStr);
        helpToFillContainer(tmpContinerStr, "157","1","222","234");
            expectedAfterSplitBytes.emplace_back(tmpContinerStr);
        helpToFillContainer(tmpContinerStr, "157","84","232","134");
            expectedAfterSplitBytes.emplace_back(tmpContinerStr);
        helpToFillContainer(tmpContinerStr, "113","162","145","156");
            expectedAfterSplitBytes.emplace_back(tmpContinerStr);

        //expected after converting
        std::vector<int> tmpContinerInt;
        helpToFillContainer(tmpContinerInt, 113,162,145,156);
            expectedAfterConvering.emplace_back(tmpContinerInt);
        helpToFillContainer(tmpContinerInt, 157,39,22,224);
            expectedAfterConvering.emplace_back(tmpContinerInt);
        helpToFillContainer(tmpContinerInt, 113,162,145,156);
            expectedAfterConvering.emplace_back(tmpContinerInt);
        helpToFillContainer(tmpContinerInt, 157,1,222,234);
            expectedAfterConvering.emplace_back(tmpContinerInt);
        helpToFillContainer(tmpContinerInt, 157,84,232,134);
            expectedAfterConvering.emplace_back(tmpContinerInt);
        helpToFillContainer(tmpContinerInt, 113,162,145,156);
            expectedAfterConvering.emplace_back(tmpContinerInt);

        //expected after sorting
        helpToFillContainer(tmpContinerInt, 157,84,232,134);
            expectedSortedContainer.emplace_back(tmpContinerInt);
        helpToFillContainer(tmpContinerInt, 157,39,22,224);
            expectedSortedContainer.emplace_back(tmpContinerInt);
        helpToFillContainer(tmpContinerInt, 157,1,222,234);
            expectedSortedContainer.emplace_back(tmpContinerInt);
        helpToFillContainer(tmpContinerInt, 113,162,145,156);
            expectedSortedContainer.emplace_back(tmpContinerInt);
        helpToFillContainer(tmpContinerInt, 113,162,145,156);
            expectedSortedContainer.emplace_back(tmpContinerInt);
        helpToFillContainer(tmpContinerInt, 113,162,145,156);
            expectedSortedContainer.emplace_back(tmpContinerInt);

        //expected after filter(113,162)
        helpToFillContainer(tmpContinerInt, 113,162,145,156);
            expectedFiltredFirst.emplace_back(tmpContinerInt);
        helpToFillContainer(tmpContinerInt, 113,162,145,156);
            expectedFiltredFirst.emplace_back(tmpContinerInt);
        helpToFillContainer(tmpContinerInt, 113,162,145,156);
            expectedFiltredFirst.emplace_back(tmpContinerInt);

        //expected after filter(157)
        helpToFillContainer(tmpContinerInt, 157,84,232,134);
            expectedFiltredSecond.emplace_back(tmpContinerInt);
        helpToFillContainer(tmpContinerInt, 157,39,22,224);
            expectedFiltredSecond.emplace_back(tmpContinerInt);
        helpToFillContainer(tmpContinerInt, 157,1,222,234);
            expectedFiltredSecond.emplace_back(tmpContinerInt);
        
        //expected after filter_any(84)
        helpToFillContainer(tmpContinerInt, 157,84,232,134);
            expectedFiltredAny.emplace_back(tmpContinerInt);
    }
    
    void createTestFile()
    {
        std::ofstream file("unitTestFile.csv");

        for(auto ip = unitTestFileContent.cbegin(); ip != unitTestFileContent.cend(); ++ip)
            file << *ip << "\n";

        std::ofstream fileSecond("unitTestFileSecond.csv");

        for(auto ip = unitTestFileSecondContent.cbegin(); ip != unitTestFileSecondContent.cend(); ++ip)
            file << *ip << "\n";
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


TEST(checkVersion, VersionController)
{
    ASSERT_TRUE(UnitTests::checkBuildVersion());
};


TEST(checkRegexp, regexpController)
{
    ASSERT_EQ(0, UnitTests::checkRegexp());
};
 

TEST(openAndPrepareContentFromFile, FillBufferOfFilenamesTest)
{
    UnitTests::prepareData();
    UnitTests::createTestFile();

    vectStr sample;

    globArgc = 3;

    globArgv[1] = new char[UnitTests::listOfFiles.at(0).size()];
    globArgv[2] = new char[UnitTests::listOfFiles.at(1).size()];

    strcpy(globArgv[1], UnitTests::listOfFiles.at(0).c_str());
    strcpy(globArgv[2], UnitTests::listOfFiles.at(1).c_str());

    sample = setListOfFilesInVector(globArgc, globArgv);

    ASSERT_TRUE(!sample.empty());
    ASSERT_EQ(globArgc - 1, sample.size()); // - 1 because first(0) calling in argc is the calling of program 
    ASSERT_TRUE(std::equal(sample.begin(), sample.end(), UnitTests::listOfFiles.begin(),UnitTests::listOfFiles.end()));
    
};


TEST(openAndPrepareContentFromFile, FillContentFromfileTest)
{
    std::string content;
    checkFilesForOpenAndFillMainContent(UnitTests::listOfFiles, content);

    ASSERT_TRUE(!content.empty());
    ASSERT_EQ(0, content.compare(UnitTests::globContentFrmFiles));
}; 


TEST(splitAndCheckForTrash, PrepareInformationTest)
{
    std::vector<std::string> factFromTestFile(split(UnitTests::globContentFrmFiles,'\n'));

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


TEST(convertToIntContainerAndSort, SplitBytesAndPrepareToConveringTest)
{
    vectVectStr ipBytesStr;

    for(size_t i = 0 ; i < UnitTests::expectedAfterCheckForTrash.size() ; i++)
    {
        ipBytesStr.push_back(split(UnitTests::expectedAfterCheckForTrash.at(i), '.'));
    }

    ASSERT_EQ(true, !ipBytesStr.empty());
    ASSERT_TRUE(std::equal(ipBytesStr.begin(), ipBytesStr.end(),UnitTests::expectedAfterSplitBytes.begin(), UnitTests::expectedAfterSplitBytes.end()));
};


TEST(convertToIntContainerAndSort, ConvertContainersTest)
{
    vectVectInt ip;

    ip = convertToInt(UnitTests::expectedAfterSplitBytes);

    ASSERT_EQ(true, !ip.empty());

    ASSERT_TRUE(std::equal(ip.begin(), ip.end(),UnitTests::expectedAfterConvering.begin(), UnitTests::expectedAfterConvering.end()));
};


TEST(SortAndFilter, SortingContainerTest)
{
    vectVectInt ip = UnitTests::expectedAfterConvering;
    
    sortIp(ip);

    ASSERT_EQ(true, !ip.empty());
    ASSERT_TRUE(std::equal(ip.begin(), ip.end(),UnitTests::expectedSortedContainer.begin(), UnitTests::expectedSortedContainer.end()));
};


TEST(SortAndFilter, FilterTest)
{
    vectVectInt sample = filter(UnitTests::expectedSortedContainer, 113,162);
    vectVectInt sampleSecond = filter(UnitTests::expectedSortedContainer, 157);

    ASSERT_EQ(true, !sample.empty());
    ASSERT_TRUE(std::equal(sample.begin(), sample.end(),UnitTests::expectedFiltredFirst.begin(), UnitTests::expectedFiltredFirst.end()));

    ASSERT_EQ(true, !sampleSecond.empty());
    ASSERT_TRUE(std::equal(sampleSecond.begin(), sampleSecond.end(),UnitTests::expectedFiltredSecond.begin(), UnitTests::expectedFiltredSecond.end()));
};


TEST(SortAndFilter, FilterAnyTest)
{
    vectVectInt sample = filter_any(UnitTests::expectedSortedContainer, 84);

    ASSERT_EQ(true, !sample.empty());
    ASSERT_TRUE(std::equal(sample.begin(), sample.end(),UnitTests::expectedFiltredAny.begin(), UnitTests::expectedFiltredAny.end()));
};


TEST(SortAndFilter, PrepareContainerTest)
{
    vectVectInt sample = prepareIpContainer(UnitTests::expectedAfterControlСharSplit);
    
    ASSERT_EQ(true, !sample.empty());
    ASSERT_TRUE(std::equal(sample.begin(), sample.end(),UnitTests::expectedAfterConvering.begin(), UnitTests::expectedAfterConvering.end()));
};


TEST(WriteInFile, WriteInFileTest)
{
    vectVectInt doneTestFile; 
    std::string content, expectedFinalContent;
    doneTestFile.insert(doneTestFile.end(), UnitTests::expectedSortedContainer.begin(), UnitTests::expectedSortedContainer.end());
    doneTestFile.insert(doneTestFile.end(), UnitTests::expectedFiltredFirst.begin(), UnitTests::expectedFiltredFirst.end());
    doneTestFile.insert(doneTestFile.end(), UnitTests::expectedFiltredSecond.begin(), UnitTests::expectedFiltredSecond.end());
    doneTestFile.insert(doneTestFile.end(), UnitTests::expectedFiltredAny.begin(), UnitTests::expectedFiltredAny.end());

    writeInFile(doneTestFile);

    std::ifstream file("ip_filter_csv_done.csv");
    
    if(!file)
    {
        FAIL();
    }
    else
    {
        content.assign(std::istreambuf_iterator<char>(file),std::istreambuf_iterator<char>());                
        file.close();
    }
    
    expectedFinalContent = UnitTests::finalStrBuilder(doneTestFile);

    ASSERT_EQ(0,content.compare(expectedFinalContent));
};