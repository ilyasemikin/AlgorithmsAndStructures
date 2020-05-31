#pragma once

#include <algorithm>

namespace learn {
    template <typename RandomIt, typename Compare>
    void bubble_sort(RandomIt begin, RandomIt end, Compare comp) {
        for (auto i = begin + 1; i < end; i++)
            for (auto j = begin; j < i; j++)
                if (comp(*i, *j))
                    std::iter_swap(i, j);
    }

    template <typename RandomIt>
    void bubble_sort(RandomIt begin, RandomIt end) {
        bubble_sort(begin, end, [](const auto &x, const auto &y) { return x < y; });
    }
}