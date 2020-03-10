# ip_filter_csv
Ip filter from csv

> OS: Linux. compiler: clang version 9.0.0-2. The build process: CMake.

#### Travis build status
[[Build Status](https://travis-ci.org/DimKush/ip_filter_csv)]

## Ip filter csv
This application processing ip for validation bytes.
You giving .csv files like arguments in command line then you calling the application.
Example: 
>ip_filter_csv.out path/to/your/csv/example.csv path/to/your/second/csv/exampleSecond.csv 

## Format of csv file
Test csv file must has format like file witch stated in /contentSample directory.
For example: simple row in .csv file has a type like this:
> 1233.444.123.44;2344sfgd;5345354;erte;34534;44444
Columns must be splited by ';' symbol.

## Ip filter csv unit tests


## Process of application
When you give .csv file to application, application start the process. The process includes steps:

[First step](https://github.com/DimKush/ip_filter_csv/blob/master/libSource/libSource.cpp#L10)
Application making std::vector<std::string> of files names witch was move from command line.   
