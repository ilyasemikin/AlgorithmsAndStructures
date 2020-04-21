#include "prefix.hpp"

namespace learn {
    std::vector<size_t> prefix_function(std::string_view str) {
        if (str.empty())
            return {};

        std::vector<size_t> ret(str.size());

        ret[0] = 0;
        size_t j;
        for (size_t i = 1; i < str.size(); i++) {
            j = ret[i - 1];

            while (j > 0 && str[j] != str[i])
                j = ret[j - 1];
            if (str[j] == str[i])
                j++;

            ret[i] = j;
        }

        return ret;
    }
}