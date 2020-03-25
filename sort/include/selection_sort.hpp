#pragma once

#include "sort_method.hpp"

namespace learn {
    template <typename T>
    void selection_sort(T *array, size_t size, compare_func<T> cmp) {
        size_t index;
        for (size_t i = 0; i < size - 1; i++) {
            index = i;
            for (size_t j = index + 1; j < size; j++)
                if (cmp(array[index], array[j]) == comparsion_result::more)
                    index = j;
            if (index != i)
                std::swap(array[index], array[i]);
        }
    }

    template <typename T>
    void selection_sort(T *array, size_t size, sort_order order) {
        if (order == sort_order::ascending)
            selection_sort(array, size, &compare_for_ascending<T>);
        else
            selection_sort(array, size, &compare_for_descending<T>);
    }
}