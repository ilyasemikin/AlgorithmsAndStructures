#include <unordered_map>
#include "string_find_substr.hpp"
using namespace std;

namespace learn::find_substr {
    unordered_map<char, size_t> get_shift_table(string_view str) {
        unordered_map<char, size_t> ret;
        
        size_t shift = 0;
        for (size_t i = str.length() - 1; i > 0; i--) {
            auto c = str[i - 1];
            
            shift++;
            if (!ret.count(c))
                ret[c] = shift;
        }

        auto last_c = str[str.length() - 1];
        if (!ret.count(last_c))
            ret[last_c] = str.length();

        return ret;
    }
    
    size_t BMH(string_view str, string_view substr) {
        if (substr.length() > str.length())
            return not_found;

        auto shift_table = get_shift_table(substr);
        size_t i = substr.length() - 1;
        while (i < str.length()) {
            size_t j = substr.length();
            while (j > 0 && substr[j - 1] == str[i + j - substr.length()])
                j--;
            
            if (j == 0)
                return i - substr.length() + 1;

            i += shift_table.count(str[i]) ? shift_table[str[i]] : substr.length();
        }
        return not_found;
    }
}