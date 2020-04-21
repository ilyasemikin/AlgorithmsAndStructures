#include "string_find.hpp"
#include "prefix.hpp"

namespace learn {
    size_t find_substr(std::string_view str, std::string_view substr) {
        if (str.empty() || substr.empty())
            return std::string_view::npos;

        size_t i = 0;
        size_t i_sub = 0;
        auto prefixs = prefix_function(substr);
        while (true) {
            if (i_sub == substr.size())
                return i - substr.size();
            if (i == str.size())
                return std::string_view::npos;

            if (str[i] == substr[i_sub]) {
                i++;
                i_sub++;
            }
            else if (i_sub == 0)
                i++;
            else
                i_sub = prefixs[i_sub - 1];
        }
    }
}