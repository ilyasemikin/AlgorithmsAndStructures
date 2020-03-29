#pragma once

#include <vector>
#include "sort_method.hpp"

namespace learn {
    template <typename T>
    void merge(T *array, size_t begin, size_t middle, size_t end, const compare_func<T> &cmp) {
        size_t left_size, right_size;
        left_size = middle - begin + 1;
        right_size = end - middle;

        std::vector<T> left(left_size);
        std::vector<T> right(right_size);

        for (size_t i = 0; i < left_size; i++)
            left[i] = array[begin + i];
        for (size_t i = 0; i < right_size; i++)
            right[i] = array[middle + 1 + i];
        
        size_t i_left, i_right;
        i_left = i_right = 0;

        size_t i = begin;
        for (; i_left < left_size && i_right < right_size; i++)
            if (cmp(left[i_left], right[i_right]) == comparsion_result::less)
                array[i] = left[i_left++];
            else
                array[i] = right[i_right++];
        
        for (; i_left < left_size; i_left++)
            array[i++] = left[i_left];
        for (; i_right < right_size; i_right++)
            array[i++] = right[i_right];
    }

    template <typename T>
    void merge_sort(T *array, size_t begin, size_t end, const compare_func<T> &cmp) {
        if (begin < end) {
            size_t middle = begin + (end - begin) / 2;
            merge_sort(array, begin, middle, cmp);
            merge_sort(array, middle + 1, end, cmp);
            merge(array, begin, middle, end, cmp);
        }
    }

    template <typename T>
    void merge_sort(T *array, size_t size, sort_order order) {
        if (order == sort_order::ascending)
            merge_sort(array, 0, size - 1, compare_for_ascending<T>);
        else
            merge_sort(array, 0, size - 1, compare_for_descending<T>);
    }
}