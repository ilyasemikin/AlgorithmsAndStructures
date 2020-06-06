#include "string_find_substr.hpp"
#include "prefix.hpp"
using namespace std;

namespace learn::find_substr {
    size_t KMP(string_view str, string_view substr) {
        if (str.empty() || substr.empty())
            return not_found;

        size_t i = 0;
        size_t i_sub = 0;
        auto prefixs = prefix_function(substr);
        while (true) {
            if (i_sub == substr.size())
                return i - substr.size();
            if (i == str.size())
                return not_found;

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