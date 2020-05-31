#pragma once

#include <algorithm>

namespace learn::sort_array {
    template <typename T, typename Compare>
    void bubble_sort(T *array, size_t size, Compare comp) {
        for (size_t i = 0; i < size; i++)
            for (size_t j = 0; j < size - i - 1; j++)
                if (comp(array[j + 1], array[j]))
                    std::swap(array[j + 1], array[j]);
    }

    template <typename T>
    void bubble_sort(T *array, size_t size) {
        bubble_sort(array, size, [](const auto &x, const auto &y) { return x < y; });
    }
}