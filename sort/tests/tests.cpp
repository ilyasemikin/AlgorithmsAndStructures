#include <gtest/gtest.h>
#include <string>
#include <functional>
#include "sort_method.hpp"
#include "insertion_sort.hpp"

using func_sort = std::function<void(int *, size_t, learn::sort_order)>;

#define FUNC_SORT_PAIR(name, f) std::pair(name, static_cast<void (*)(int *, size_t, learn::sort_order)>(&f))

class sort_test : 
    public testing::TestWithParam<std::pair<std::string, func_sort>>
{

};

TEST_P(sort_test, 3_items_sort_asc) {
    // Arrange
    int array[] { 2, 1, 0 };
    int expected_array[] { 0, 1, 2 };
    size_t size = sizeof(expected_array) / sizeof(int);

    // Act
    GetParam().second(array, size, learn::sort_order::ascending);

    // Assert
    for (size_t i = 0; i < size; i++)
        ASSERT_EQ(array[i], expected_array[i]);
}

TEST_P(sort_test, 3_items_sort_dec) {
    // Arrange
    int array[] { 0, 1, 2 };
    int expected_array[] { 2, 1, 0 };
    size_t size = sizeof(expected_array) / sizeof(int);

    // Act
    GetParam().second(array, size, learn::sort_order::descending);

    // Assert
    for (size_t i = 0; i < size; i++)
        ASSERT_EQ(array[i], expected_array[i]);
}

INSTANTIATE_TEST_CASE_P(
    instantiation_sort_test, 
    sort_test, 
    testing::Values(
        FUNC_SORT_PAIR("insertion", learn::insertion_sort<int>)
    )
);

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}