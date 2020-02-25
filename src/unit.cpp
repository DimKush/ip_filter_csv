#include <gtest/gtest.h>

int globArgc; 
char **globArgv;

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    
    globArgc = argc;
    globArgv = argv;
    
    return RUN_ALL_TESTS();
}
