#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <regex>

#include <boost/log/trivial.hpp>



using vectVectStr = std::vector<std::vector<std::string>>;
using vectVectInt = std::vector<std::vector<int>>;
using vectStr     = std::vector<std::string>;
using vectInt     = std::vector<int>;


auto checkFilesForOpenAndFillMainContent(vectStr const & bufferOfFilesNames, std::string & mainContent)
{
      std::ifstream file;

      for(size_t i = 0 ; i < bufferOfFilesNames.size(); i++)
      {
          file.open(bufferOfFilesNames.at(i));

          if(!file)
          {
              BOOST_LOG_TRIVIAL(info) << "Cant find file : " << bufferOfFilesNames.at(i);
          }
          else
          {
              mainContent.assign(std::istreambuf_iterator<char>(file),std::istreambuf_iterator<char>());
              file.close();
          }
      }
}


auto setListOfFilesInVector(int &argc, char *argv[])
{
    vectStr bufferOfFilesNames;
    
    for(auto i = 1 ; i < argc; i++)
    {
        bufferOfFilesNames.emplace_back(std::string(*(argv + i)));
    }

    return bufferOfFilesNames;
}


vectStr split(std::string const & str, char symbol)
{
    vectStr tmpContainer;

    std::string::size_type  beginPos = 0, endPos = str.find_first_of(symbol);

    while(endPos != std::string::npos)
    {
        tmpContainer.push_back(str.substr(beginPos,endPos - beginPos));

        beginPos = endPos + 1;
        endPos = str.find_first_of(symbol, beginPos);
    }

    tmpContainer.push_back(str.substr(beginPos));

    return tmpContainer;
}


bool lexiCompare(const vectInt &a, const vectInt &b)
{
    return std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
}


void sortIp(vectVectInt & ip)
{
    std::sort(ip.rbegin(), ip.rend(), lexiCompare);
}



inline void show(vectVectStr & ipList)
{ 
     for(auto ip = ipList.cbegin(); ip != ipList.cend(); ++ip)
     {
            for(auto ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
            {
                if (ip_part != ip->cbegin())
                {
                    std::cout << ".";
                }
                std::cout << *ip_part;
            }
            std::cout << std::endl;
     }
}


inline void show(vectVectInt & ipList)
{ 
     for(auto ip = ipList.cbegin(); ip != ipList.cend(); ++ip)
     {
            for(auto ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
            {
                if (ip_part != ip->cbegin())
                {
                    std::cout << ".";
                }
                std::cout << *ip_part;
            }
            std::cout << std::endl;
     }
}


vectVectInt filter_any(vectVectInt & vInside, int param)
{
    vectVectInt ipSorted;
 
    std::for_each(vInside.begin(), vInside.end(), [&ipSorted, param](const vectInt & element)
    {
        auto pos = std::any_of(element.begin(),element.end(),[=](int byteStr)
        {
            return param == byteStr;
        });
 
        if(pos)
        {
            ipSorted.emplace_back(element);
        }
    });
    
    return ipSorted;
}


template<typename ... Args>
vectVectInt filter(vectVectInt & ipBytes, const Args ... args)
{
    vectVectInt ipSorted;
    
    vectInt forSearch;
        
    (forSearch.emplace_back(args),...);

    std::for_each(ipBytes.begin(), ipBytes.end(), [&ipSorted,&forSearch](const vectInt & element)
    {
        bool pos = std::equal(forSearch.begin(), forSearch.end(), element.begin());

        if(pos)
        {
            ipSorted.emplace_back(element);
        }
    });

    return ipSorted;
}


void checkForTrash(vectStr & ipForCheck)
{
    std::regex regIp("^((25[0-5]|2[0-4][\\d]|1[\\d][\\d]|[\\d]?[\\d])[\\.,\\s]){3}(25[0-5]|2[0-4][\\d]|1[\\d][\\d]|[\\d]?[\\d])$");
    
    for(size_t i = 0 ; i < ipForCheck.size() ; i++)
    {
        if(!std::regex_match(ipForCheck.at(i), regIp))
        {
            std::cout << "drop ipForCheck.at(i) = " << ipForCheck.at(i) << std::endl;
            ipForCheck.erase(ipForCheck.begin() + i);
            i -= 1; // because counts of elements in vector after erase are decreasing but number of iteration must be same
        }
    }
}


vectVectInt convertToInt(const vectVectStr &ipSorted)
{
    vectVectInt ip;
    vectInt ipByte; 

    std::for_each(ipSorted.begin(), ipSorted.end(), [&ip, &ipByte](std::vector<std::string> element)
    {  
        ipByte.clear();

        std::for_each(element.begin(), element.end(), [&ipByte](std::string byteStr)
        {
            ipByte.emplace_back(std::stoi(byteStr));
        });

        ip.emplace_back(ipByte);
    });

    return ip;
}


int main(int argc, char* argv[])
{
    std::string mainContent;
    vectStr rows;
    vectVectStr ipBytesStr;
    vectVectInt ip, filtredIp;

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

    show(ip);
    
    std::cout << "---------------------FILTERED---------------------" << std::endl;
    filtredIp = filter(ip, 1);
    show(filtredIp);
    
    std::cout << "------------FILTER BY 46 AND 70--------------" << std::endl;
    filtredIp = filter(ip, 46,70);
    show(filtredIp);
    
    std::cout << "------------FILTER BY ANY OF 46 --------------------" << std::endl;
    filtredIp = filter_any(ip, 46);
    show(filtredIp);
    
    return 0;
}