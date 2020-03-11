# ip_filter_csv
> OS: Linux. compiler: clang version 9.0.0-2. The build process: CMake.

#### Travis build status
[[Build Status](https://travis-ci.org/DimKush/ip_filter_csv)]

## Ip filter csv
This application processing ip for validation bytes.
You giving .csv files like arguments in command line when you calling the application.
Example: 
>ip_filter_csv.out path/to/your/csv/example.csv path/to/your/second/csv/exampleSecond.csv 

## Format of csv file
Test csv file must has format like file witch stated in /contentSample directory.
For example: simple row in .csv file has a type like this:

> 10.10.10.1;just;sample;text;...

Columns must be splited by ';' symbol.

## Ip filter csv unit tests


## Process of application
When you give .csv file to application, application start the process. The process includes steps:

[First step](https://github.com/DimKush/ip_filter_csv/blob/master/libSource/libSource.cpp#L10)
Application making std::vector of std::string of files names witch was move from command line in this container for processing.

[Second step](https://github.com/DimKush/ip_filter_csv/blob/master/libSource/libSource.cpp#L23)
Application try to open your .csv files and save content from .csv files to the big std::string witch will be processing later.
If one of the files list from command line cannot be opened, application will pass this file, and it will write string to command line like

>Cannot find file : path/to/your/csv/example.

[Third step](https://github.com/DimKush/ip_filter_csv/blob/master/libSource/libSource.cpp#L73) When std::string has full information from .csv files, application spliting it like rows and putting it to the std::vector of std::string container like elements of it.

[Fourth step](https://github.com/DimKush/ip_filter_csv/blob/master/libSource/libSource.cpp#L196) In this step application took container with cut rows to the functionality of cleaning. This functionality finding std::string which has content like in the regexp expression.
If string has content not like in regexp expression, application write string in comand line:

> "Elemnent something was dropped.";

And miss it.

[Five step](https://github.com/DimKush/ip_filter_csv/blob/master/libSource/libSource.cpp#L99) After cleaning, application will sort container of ip bytes.
