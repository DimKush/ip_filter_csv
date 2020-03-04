#pragma once
#include <algorithm>

namespace libSource
{
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
};