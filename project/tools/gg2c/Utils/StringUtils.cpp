#include "StringUtils.h"
#include <algorithm>

std::string StringUtils::str_toupper(std::string s)
{
    std::transform(s.begin(), s.end(), s.begin(), 
                   [](unsigned char c){ return std::toupper(c); } // correct
                  );
    return s;
}
