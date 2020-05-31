#pragma once

namespace learn::sort_array {
    template <typename T, typename Compare>
    size_t partition(T *array, size_t left, size_t right, Compare comp) {
        auto middle = left + (right - left) / 2;
        
        size_t i = left;
        size_t j = right;
        do {
            while (comp(array[middle], array[j]))
                j--;
            while (!comp(array[middle], array[i]))
                i++;
            if (i < j) {
                std::swap(array[i], array[j]);
                i++;
                j--;
            }
        } while (i < j);
        return middle;
    }

    template <typename T, typename Compare>
    void quick_sort(T *array, size_t size, Compare comp) {
        if (size > 1) {
            auto middle = partition(array, 0, size - 1, comp);
            quick_sort(array, middle, comp);
            quick_sort(array + middle + 1, size - middle - 1, comp);
        }
    }

    template <typename T>
    void quick_sort(T *array, size_t size) {
        quick_sort(array, size, [](const auto &x, const auto &y) { return x < y; });
    }
}