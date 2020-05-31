#pragma once

#include <algorithm>

namespace learn::sort_array {
    template <typename T, typename Compare>
    void heapify(T *array, size_t size, size_t index, Compare comp) {
        auto left = 2 * index + 1;
        auto right = 2 * index + 2;

        auto move_index = index;
        if (left < size && !comp(array[left], array[index]))
            move_index = left;
        if (right < size && !comp(array[right], array[move_index]))
            move_index = right;

        if (move_index != index) {
            std::swap(array[index], array[move_index]);
            heapify(array, size, move_index, comp);
        }
    }

    template <typename T, typename Compare>
    void build_heap_tree(T *array, size_t size, Compare comp) {
        for (size_t i = size / 2 + 1; i > 0; i--)
            heapify(array, size, i - 1, comp);
    }

    template <typename T, typename Compare>
    void heap_sort(T *array, size_t size, Compare comp) {
        build_heap_tree(array, size, comp);
        for (size_t i = size - 1; i > 0; i--) {
            std::swap(array[0], array[i]);
            heapify(array, i, 0, comp);
        }
    }

    template <typename T>
    void heap_sort(T *array, size_t size) {
        heap_sort(array, size, [](const auto &x, const auto &y) { return x < y; });
    }
}