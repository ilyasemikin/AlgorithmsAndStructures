#pragma once

#include <algorithm>
#include "sort_method.hpp"

namespace learn {
    template <typename T>
    void bubble_sort(T *array, size_t size, compare_func<T> cmp) {
        for (size_t i = 0; i < size; i++)
            for (size_t j = 0; j < size - i - 1; j++)
                if (cmp(array[j], array[j + 1]) == comparsion_result::more)
                    std::swap(array[j], array[j + 1]);
    }

    template <typename T>
    void bubble_sort(T *array, size_t size, sort_order order) {
        if (order == sort_order::ascending)
            bubble_sort(array, size, &compare_for_ascending<T>);
        else
            bubble_sort(array, size, &compare_for_descending<T>);
    }
}