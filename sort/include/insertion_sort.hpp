#pragma once

#include <limits>
#include <functional>

#include <iostream>

namespace learn {
    template <typename RandomIt, typename Compare>
    void insertion_sort(RandomIt begin, RandomIt end, Compare comp) {
        // https://stackoverflow.com/questions/18453945/c-generic-insertion-sort
        // Действительно интересный вариант
        for (auto it = begin; it != end; ++it)
            std::rotate(std::upper_bound(begin, it, *it, comp), it, std::next(it));
    }

    template <typename RandomIt>
    void insertion_sort(RandomIt begin, RandomIt end) {
        insertion_sort(begin, end, [](const auto &x, const auto &y) { return x < y; });
    }
}