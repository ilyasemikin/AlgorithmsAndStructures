#include <gtest/gtest.h>
#include "search.hpp"

// Так по хорошему делать не желательно, но мне сейчас лень расписывать так что так
TEST(search, tests) {
    using namespace learn::array_search;
    
    // Arrange 
    int array[] { 0, 1, 2, 3, 3, 3, 4, 5, 5, 6, 8, 9 };
    size_t size = sizeof(array) / sizeof(int);

    // Act
    // nothing

    // Assert
    EXPECT_EQ(linear_search(array, size, 3), 3);
    EXPECT_EQ(linear_search(array, size, 10), npos);

    EXPECT_EQ(linear_search_b(array, size, 3), 5);
    EXPECT_EQ(linear_search_b(array, size, 10), npos);

    EXPECT_EQ(linear_barrier_search(array, size, 0), 0);
    EXPECT_EQ(linear_barrier_search(array, size, 10), npos);
    
    EXPECT_EQ(linear_barrier_search_b(array, size, 3), 5);
    EXPECT_EQ(linear_barrier_search_b(array, size, 10), npos);

    EXPECT_EQ(binary_search(array, size, 2), 2);
    EXPECT_EQ(binary_search(array, size, 7), npos);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}