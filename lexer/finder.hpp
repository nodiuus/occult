#pragma once
#include <string>
#include <regex>

namespace occultlang 
{
    class finder 
    {
    public:
        finder() {}

        std::string match_and_replace_all(std::string source, std::string to_find,std::string to_replace);
        std::string match_and_replace_all_array(std::string source, std::string to_replace);
    };
} // occultlang