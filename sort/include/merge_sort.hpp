#pragma once

#include <algorithm>
#include <vector>

namespace learn {
    template <typename RandomIt, typename Compare>
    void merge_sort(RandomIt begin, RandomIt end, Compare comp) {
        if (begin + 1 < end) {
            auto middle = begin + (end - begin) / 2;
            merge_sort(begin, middle, comp);
            merge_sort(middle, end, comp);
            std::inplace_merge(begin, middle, end, comp);
        }
    }

    template <typename RandomIt>
    void merge_sort(RandomIt begin, RandomIt end) {
        merge_sort(begin, end, [](const auto &x, const auto &y) { return x < y; });
    }
}