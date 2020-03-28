#pragma once

#include <limits>
#include <cstddef>

namespace learn::array_search {
    const size_t npos = std::numeric_limits<size_t> ::max();
    
    template <typename T>
    size_t linear_search(const T *array, size_t size, const T x) {
        for (size_t i = 0; i < size; i++)
            if (array[i] == x)
                return i;
        return npos;
    }

    template <typename T>
    size_t linear_search_b(const T *array, size_t size, const T x) {
        if (size == 0)
            return npos;

        size_t i = size - 1;
        do {
            if (array[i] == x)
                return i;
            i--;
        } while (i != 0);

        return npos;
    }

    template <typename T>
    size_t linear_barrier_search(T *array, size_t size, const T x) {
        if (size == 0)
            return 0;

        size_t i = 0;

        T temp = array[size - 1];
        array[size - 1] = x;

        while (array[i] != x)
            i++;

        array[size - 1] = temp;
        return array[i] == x ? i : npos;
    }
    
    template <typename T>
    size_t linear_barrier_search_b(T *array, size_t size, const T x) {
        if (size == 0)
            return 0;

        size_t i = size - 1;

        T temp = array[0];
        array[0] = x;

        while (array[i] != x)
            i--;

        array[0] = temp;
        return array[i] == x ? i : npos;
    }

    // Бинарный поиск в отсортированном по возрастанию массиве
    template <typename T>
    size_t binary_search(const T *array, size_t size, const T x) {
        size_t left, middle, right;
        left = 0;
        right = size - 1;
        while (left <= right) {
            middle = left + (right - left) / 2;

            if (array[middle] > x)
                right = middle - 1;
            else if (array[middle] < x)
                left = middle + 1;
            else
                return middle;
        }
        return npos;
    }
}