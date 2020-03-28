#include <gtest/gtest.h>
#include <ostream>
#include "max_subarray.hpp"

class max_subarray_test : public testing::TestWithParam<learn::max_subarray_method> {

};

TEST_P(max_subarray_test, test_1) {
    // Arrange
    int array[] { 13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7 };
    size_t size = sizeof(array) / sizeof(int);

    // Act
    auto res = learn::get_max_subarray(array, size, GetParam()); 

    // Assert
    ASSERT_EQ(res.begin, 7);
    ASSERT_EQ(res.end, 10);
    ASSERT_EQ(res.sum, 43);
}

TEST_P(max_subarray_test, test_2) {
    // Arrange
    int array[] { -15, 5, 15, -9, 10, 11, 1, 0, -15, -14, 0, 1, 2 };
    size_t size = sizeof(array) / sizeof(int);

    // Act
    auto res = learn::get_max_subarray(array, size, GetParam()); 

    // Assert
    ASSERT_EQ(res.begin, 1);
    ASSERT_EQ(res.end, 6);
    ASSERT_EQ(res.sum, 33);
}

INSTANTIATE_TEST_CASE_P(
    instantiate_max_subarray_test,
    max_subarray_test,
    testing::Values(
        learn::max_subarray_method::bruteforce,
        learn::max_subarray_method::recursion,
        learn::max_subarray_method::linear
    )
);

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}