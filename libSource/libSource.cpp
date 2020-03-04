#include <algorithm>
#include <iostream>
#include <fstream>
#include <regex>

#include "libSource.h"

namespace libSource
{
    vectStr setListOfFilesInVector(int &argc, char **argv)
    {
        vectStr bufferOfFilesNames;
        
        for(auto i = 1 ; i < argc; i++)
        {
            bufferOfFilesNames.emplace_back(std::string(*(argv + i)));
        }

        return bufferOfFilesNames;
    }


    void checkFilesForOpenAndFillMainContent(vectStr const & bufferOfFilesNames, std::string & mainContent)
    {
        std::ifstream file;
        std::string strTmp;
        for(size_t i = 0 ; i < bufferOfFilesNames.size(); i++)
        {  
            file.open(bufferOfFilesNames.at(i));

            if(!file)
            {
                std::cout << "Cant find file : " << bufferOfFilesNames.at(i);
            }
            else
            {
                strTmp.assign(std::istreambuf_iterator<char>(file),std::istreambuf_iterator<char>());
                
                mainContent += strTmp;
                
                file.close();
            }
        }
    }


    void writeInFile(const vectVectInt & ipInFile)
    {
        std::ofstream file("ip_filter_csv_done.csv");

        for(auto ip = ipInFile.cbegin(); ip != ipInFile.cend(); ++ip)
        {
            for(auto ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
            {
                if (ip_part != ip->cbegin())
                {
                    file << ".";
                }
                file << *ip_part;
            }
            file << "\n";
        }
    }


    vectVectInt& concatenateIp(vectVectInt &basicIp,vectVectInt &ip)
    {
        basicIp.insert(basicIp.end(), ip.begin(),ip.end());
        return basicIp;
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



    void show(vectVectStr & ipList)
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


    void show(vectVectInt & ipList)
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

    void checkForTrash(vectStr & ipForCheck)
    {
        std::regex regIp(REGEX_CONST);
        
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

    vectVectInt prepareIpContainer(const vectStr &rows)
    {
        std::string element;
        vectVectStr ipBytesStr;
        
        std::regex regIp("^((25[0-5]|2[0-4][\\d]|1[\\d][\\d]|[\\d]?[\\d])[\\.,\\s]){3}(25[0-5]|2[0-4][\\d]|1[\\d][\\d]|[\\d]?[\\d])$");
        
        for(auto i = rows.begin() ; i != rows.end() ; i++)
        {
            element = split(*(i),';').at(0);

            if(std::regex_match(element, regIp))
            {
                ipBytesStr.push_back(split(element, '.'));
            }
            else
            {
                std::cout << "Elemnent : " << element << " was dropped.\n";
            }
        }

        return convertToInt(ipBytesStr);
    }

};