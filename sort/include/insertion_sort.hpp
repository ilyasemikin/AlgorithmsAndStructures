#pragma once

#include <limits>
#include <functional>
#include "sort_method.hpp"

namespace learn {
    template <typename T>
    void insertion_sort(T *array, size_t size, compare_func<T> cmp) {
        size_t j;
        size_t max_value = std::numeric_limits<size_t>::max();
        for (size_t i = 1; i < size; i++) {
            auto key = array[i];
            j = i - 1;
            while (j != max_value && cmp(array[j], key) == comparsion_result::more) {
                array[j + 1] = array[j];
                j--;
            }
            array[j + 1] = key;
        }
    }

    template <typename T>
    void insertion_sort(T *array, size_t size, sort_order order) {
        if (order == sort_order::ascending)
            insertion_sort(array, size, &compare_for_ascending<int>);
        else
            insertion_sort(array, size, &compare_for_descending<int>);
    }
}