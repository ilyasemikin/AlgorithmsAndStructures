#pragma once

#include <algorithm>

namespace learn::sort_array {
    template <typename T, typename Compare>
    void merge_sort(T *array, size_t size, Compare comp) {
        if (size > 1) {
            size_t middle = size / 2;
            merge_sort(array, middle, comp);
            merge_sort(array + middle, size - middle, comp);
            std::inplace_merge(array, array + middle, array + size, comp);
        }
    }

    template <typename T>
    void merge_sort(T *array, size_t size) {
        merge_sort(array, size, [](const auto &x, const auto &y) { return x < y; });
    }
}