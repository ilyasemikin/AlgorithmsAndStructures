#pragma once

#include <algorithm>

namespace learn {
    template <typename RandomIt, typename Compare>
    void shaker_sort(RandomIt begin, RandomIt end, Compare comp) {
        if (begin == end)
            return;

        end--;
        while (begin < end) {
            for (auto it = begin; it < end; it++)
                if (comp(*(it + 1), *it))
                    std::iter_swap(it, it + 1);
            end--;

            for (auto it = end; it > begin; it--)
                if (comp(*it, *(it - 1)))
                    std::iter_swap(it - 1, it);
            begin++;
        }
    }

    template <typename RandomIt>
    void shaker_sort(RandomIt begin, RandomIt end) {
        shaker_sort(begin, end, [](const auto &x, const auto &y) { return x < y; });
    }
}