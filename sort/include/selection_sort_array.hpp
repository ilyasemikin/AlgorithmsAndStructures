#pragma once

#include <algorithm>

namespace learn::sort_array {
    template <typename T, typename Compare>
    void selection_sort(T *array, size_t size, Compare comp) {
        for (size_t i = 0; i < size - 1; i++) {
            size_t swaped = i;
            for (size_t j = i + 1; j < size; j++)
                if (comp(array[j], array[swaped]))
                    swaped = j;

            if (swaped != i)
                std::swap(array[i], array[swaped]);
        }
    }

    template <typename T>
    void selection_sort(T *array, size_t size) {
        selection_sort(array, size, [](const auto &x, const auto &y) { return x < y; });
    }
}