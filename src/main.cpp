#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <regex>


using vectVectStr = std::vector<std::vector<std::string>>;
using vectStr = std::vector<std::string>;


auto checkFilesForOpenAndFillMainContent(vectStr const & bufferOfFilesNames, std::string & mainContent)
{
      std::ifstream file;

      for(size_t i = 0 ; i < bufferOfFilesNames.size(); i++)
      {
          file.open(bufferOfFilesNames.at(i));

          if(!file)
          {
              std::cout << "Cant find file : " << bufferOfFilesNames.at(i) << std::endl;
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


// template<typename ... Types>
void checkIpBytesForValid(vectStr & vectForCheck)
{
    auto valForCheck = 0;

    for(int j = 0 ; j < 4 ; j++)
    {
        valForCheck = std::stoi(vectForCheck.at(j)); 
        std::cout << "val = " << valForCheck << std::endl;
        std::cout << vectForCheck.at(j) << std::endl;
        
        if(valForCheck > 255)
        {
            vectForCheck.at(j) = "255";
        }
        else if(valForCheck < 0)
        {
            vectForCheck.at(j) = "0";
        }

        std::cout << '\t'<< vectForCheck.at(j) << std::endl;
    }
    return;
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


void sortIp(vectVectStr & ipList)
{
    std::sort(ipList.rbegin(), ipList.rend());
}


vectVectStr filter_any(vectVectStr & vInside, int param)
{
    vectVectStr ipSorted;
 
    std::for_each(vInside.begin(), vInside.end(), [&ipSorted, param](const vectStr & element)
    {
        auto pos = std::any_of(element.begin(),element.end(),[=](std::string byteStr)
        {
            return std::to_string(param) == byteStr;
        });
 
        if(pos)
        {
            ipSorted.emplace_back(element);
        }
    });
    
    return ipSorted;
}


template<typename ... Args>
vectVectStr filter(vectVectStr & ipBytesStr, const Args ... args)
{
    vectVectStr ipSorted;
    
    std::for_each(ipBytesStr.begin(), ipBytesStr.end(), [&ipSorted,args...](const vectStr & element)
    {
        vectStr forSearch;
        (forSearch.emplace_back(std::to_string(args)), ...);
        
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

void sort(vectVectStr & ipBytesStr)
{

}


int main(int argc, char* argv[])
{
    std::string mainContent;
    vectStr rows;
    vectVectStr ipBytesStr, filtredIp;
    
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
    
    show(ipBytesStr);
    
    std::cout << "------------FILTER BY 1 ---------------------" << std::endl;
    filtredIp = filter(ipBytesStr, 1);
    show(filtredIp);
    
    std::cout << "------------FILTER BY 46 AND 70--------------" << std::endl;
    filtredIp = filter(ipBytesStr, 46,70);
    show(filtredIp);

    std::cout << "------------FILTER BY ANY OF 46 --------------------" << std::endl;
    filtredIp = filter_any(ipBytesStr, 46);
    show(filtredIp);

    return 0;
}