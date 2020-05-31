#pragma once

namespace learn {
    // TODO: реализовать
    template <typename RandomIt, typename Compare>
    void quick_sort(RandomIt begin, RandomIt end, Compare comp) {

    }

    template <typename RandomIt>
    void quick_sort(RandomIt begin, RandomIt end) {
        quick_sort(begin, end, [](const auto &x, const auto &y) { return x < y; });
    }
}