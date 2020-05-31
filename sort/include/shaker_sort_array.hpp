#pragma once

#include <algorithm>

namespace learn::sort_array {
    template <typename T, typename Compare>
    void shaker_sort(T *array, size_t size, Compare comp) {
        if (size == 0)
            return;
        
        size_t left = 0;
        size_t right = size - 1;

        while (left < right) {
            for (size_t i = left; i < right; i++)
                if (comp(array[i + 1], array[i]))
                    std::swap(array[i], array[i + 1]);
            right--;

            for (size_t i = right; i > left; i--)
                if (comp(array[i], array[i - 1]))
                    std::swap(array[i - 1], array[i]);
            left++;
        }
    }

    template <typename T>
    void shaker_sort(T *array, size_t size) {
        shaker_sort(array, size, [](const auto &x, const auto &y) { return x < y; });
    }
}