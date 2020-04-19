#include <algorithm>
#include <string>

#include "string_split.hpp"

namespace learn {
    std::vector<std::string> split_into_words(const std::string &input) {
        std::vector<std::string> ret;
        
        auto first_not_delim = [](char c) {
            return c != ' ';
        };

        auto begin_it = std::find_if(input.begin(), input.end(), first_not_delim);
        const auto end_it = input.end();

        while (begin_it != end_it) {
            auto it = std::find(begin_it, end_it, ' ');

            ret.push_back({ begin_it, it });

            begin_it = std::find_if(it, end_it, first_not_delim);
        }

        return ret;
    }
}