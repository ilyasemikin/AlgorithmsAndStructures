#pragma once

#include <algorithm>

namespace learn {
    

    template <typename RandomIt, typename Compare>
    void selection_sort(RandomIt begin, RandomIt end, Compare comp) {
        for (auto i = begin; i < end - 1; i++) {
            auto swaped = i;
            for (auto j = i + 1; j < end; j++)
                if (comp(*j, *swaped))
                    swaped = j;
            
            if (swaped != i)
                std::iter_swap(i, swaped);
        }
    }

    template <typename RandomIt>
    void selection_sort(RandomIt begin, RandomIt end) {
        selection_sort(begin, end, [](const auto &x, const auto &y) { return x < y; });
    }
}