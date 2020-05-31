#pragma once

#include <algorithm>

namespace learn {
    template <typename RandomIt, typename Compare>
    void heap_sort(RandomIt begin, RandomIt end, Compare comp) {
        std::make_heap(begin, end, comp);
        while (begin != end)
            std::pop_heap(begin, end--, comp);
    }

    template <typename RandomIt>
    void heap_sort(RandomIt begin, RandomIt end) {
        heap_sort(begin, end, [](const auto &x, const auto &y) { return x < y; });
    }
}