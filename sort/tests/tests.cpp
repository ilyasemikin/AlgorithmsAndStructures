#include <gtest/gtest.h>
#include <string>
#include <iostream>
#include <functional>
#include <vector>

#include "sort_methods.hpp"

template <typename T>
struct func_array_sort_desc {
    std::string name;
    std::function<void(T *, size_t)> function;
};

template <typename T>
std::ostream &operator<<(std::ostream &str, const func_array_sort_desc<T> &desc) {
    return str << desc.name;
}

using type = int;

class sort_array_test : 
    public testing::TestWithParam<func_array_sort_desc<type>>
{

};

TEST_P(sort_array_test, 9_items_sort) {
    // Arrange
    type array[] { 5, 7, 1, 4, 3, 9, 2, 6, 8 };
    type expected_array[] { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    size_t size = sizeof(array) / sizeof(type);

    // Act
    GetParam().function(array, size);

    // Assert
    for (size_t i = 0; i < size; i++)
        ASSERT_EQ(array[i], expected_array[i]);
}

INSTANTIATE_TEST_CASE_P(
    instantiation_sort_array_test, 
    sort_array_test, 
    testing::Values(
        func_array_sort_desc<type>{ "bubble",       learn::sort_array::bubble_sort<type> },
        func_array_sort_desc<type>{ "selection",    learn::sort_array::selection_sort<type> },
        func_array_sort_desc<type>{ "insertion",    learn::sort_array::insertion_sort<type> },
        func_array_sort_desc<type>{ "merge",        learn::sort_array::merge_sort<type> },
        func_array_sort_desc<type>{ "heap",         learn::sort_array::heap_sort<type> },
        func_array_sort_desc<type>{ "quick",        learn::sort_array::heap_sort<type> },
        func_array_sort_desc<type>{ "shaker",       learn::sort_array::shaker_sort<type> }
    )
);

template<typename RandomIt>
struct func_iter_sort_desc {
    std::string name;
    std::function<void(RandomIt, RandomIt)> function;
};

template <typename T>
std::ostream &operator<<(std::ostream &str, const func_iter_sort_desc<T> &desc) {
    return str << desc.name;
}

using iterator_type = std::vector<type>::iterator;

class sort_iterator_test : 
    public testing::TestWithParam<func_iter_sort_desc<iterator_type>>
{

};

TEST_P(sort_iterator_test, 9_items_sort) {
    // Arrange
    std::vector<type> array { 5, 7, 1, 4, 3, 9, 2, 6, 8 };
    std::vector<type> expected_array { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    // Act
    GetParam().function(array.begin(), array.end());

    // Assert
    ASSERT_EQ(array, expected_array);
}

INSTANTIATE_TEST_CASE_P(
    instantiation_sort_iterator_test, 
    sort_iterator_test, 
    testing::Values(
        func_iter_sort_desc<iterator_type>{ "bubble",       learn::bubble_sort<iterator_type> },
        func_iter_sort_desc<iterator_type>{ "selection",    learn::selection_sort<iterator_type> },
        func_iter_sort_desc<iterator_type>{ "insertion",    learn::insertion_sort<iterator_type> },
        func_iter_sort_desc<iterator_type>{ "merge",        learn::merge_sort<iterator_type> },
        func_iter_sort_desc<iterator_type>{ "heap",         learn::heap_sort<iterator_type> },
        func_iter_sort_desc<iterator_type>{ "quick",        learn::quick_sort<iterator_type> },
        func_iter_sort_desc<iterator_type>{ "shaker",       learn::shaker_sort<iterator_type> }
    )
);

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}