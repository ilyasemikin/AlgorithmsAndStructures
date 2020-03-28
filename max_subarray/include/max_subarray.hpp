#pragma once

#include <map>
#include <functional>
#include <limits>

namespace learn {
    template <typename T>
    struct subarray_info {
        size_t begin;
        size_t end;
        T sum;

        subarray_info() 
            : begin(0), end(0), sum(0)
        {

        }

        subarray_info(size_t begin, size_t end, T sum) : 
            begin(begin), end(end), sum(sum)
        {

        }
    };

    enum class max_subarray_method : int {
        bruteforce,
        recursion,
        linear
    };

    template <typename T>
    subarray_info<T> get_max_subarray_bruteforce(const T *array, size_t size) {
        subarray_info<T> ret;
        ret.sum = std::numeric_limits<T>::min();
        T sum;
        for (size_t i = 0; i < size; i++) {
            sum = 0;
            for (size_t j = i; j < size; j++) {
                sum += array[j];
                if (ret.sum < sum) {
                    ret.begin = i;
                    ret.end = j;
                    ret.sum = sum;
                }
            }
        }
        return ret;
    }

    template <typename T>
    subarray_info<T> get_max_crossing_subarray(const T *array, size_t low, size_t mid, size_t high) {
        T left_sum, right_sum;
        left_sum = right_sum = std::numeric_limits<T>::min();
        
        subarray_info<T> ret;

        T sum = 0;
        size_t i = mid;
        while (true) {
            sum += array[i];
            if (sum > left_sum) {
                left_sum = sum;
                ret.begin = i;
            }
            if (i == low)
                break;
            i--;
        };

        sum = 0;
        for (i = mid + 1; i <= high; i++) {
            sum += array[i];
            if (sum > right_sum) {
                right_sum = sum;
                ret.end = i;
            }
        }

        ret.sum = left_sum + right_sum;
        return ret;
    }

    template <typename T>
    subarray_info<T> get_max_subarray_recursion(const T *array, size_t low, size_t high) {
        if (low == high)
            return subarray_info<T>(low, high, array[low]);
        
        size_t mid_index = low + (high - low) / 2;
        auto left = get_max_subarray_recursion(array, low, mid_index);
        auto right = get_max_subarray_recursion(array, mid_index + 1, high);
        auto cross = get_max_crossing_subarray(array, low, mid_index, high);

        if (left.sum >= right.sum && left.sum >= cross.sum)
            return left;
        else if (right.sum >= left.sum && right.sum >= cross.sum)
            return right;
        return cross;
    }
    
    template <typename T>
    subarray_info<T> get_max_subarray_recursion(const T *array, size_t size) {
        return get_max_subarray_recursion(array, 0, size - 1);
    }

    template <typename T>
    subarray_info<T> get_max_subarray_linear(const T *array, size_t size) {
        subarray_info<T> ret;

        size_t start = 0;
        T sum = 0;
        for (size_t i = 0; i < size; i++) {
            sum += array[i];
            if (sum < 0) {
                sum = 0;
                start = i + 1;
            }
            else if (sum > ret.sum) {
                ret.sum = sum;
                ret.begin = start;
                ret.end = i;
            }
        }
        return ret;
    }

    template <typename T>
    subarray_info<T> get_max_subarray(const T *array, size_t size, max_subarray_method method) {
        const std::map<max_subarray_method, std::function<subarray_info<T>(const T *, size_t)>> funcs {
            { max_subarray_method::bruteforce,  &get_max_subarray_bruteforce<T> },
            { max_subarray_method::recursion,   static_cast<subarray_info<T> (*)(const T *, size_t)>(&get_max_subarray_recursion<T>) },
            { max_subarray_method::linear,      &get_max_subarray_linear<T> }
        };

        return funcs.at(method)(array, size);
    }
}