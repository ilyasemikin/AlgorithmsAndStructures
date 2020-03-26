#include <string>
#include <ostream>
#include <gtest/gtest.h>
#include "matrix.hpp"

TEST(matrix_test, one_line_initializer_list_construct) {
    // Arrange
    std::vector<int> expected_items { 0, 1, 2, 3 };
    learn::matrix<int> mx { 0, 1, 2, 3 };

    // Act
    // nothing

    // Assert
    ASSERT_EQ(mx.get_m(), 1);
    ASSERT_EQ(mx.get_n(), expected_items.size());
    for (size_t j = 0; j < expected_items.size(); j++)
        ASSERT_EQ(mx.at(0, j), expected_items[j]);
}

TEST(matrix_test, few_lines_init_list_construct) {
    // Arrange
    std::vector<std::vector<int>> expected_items = {
        { 0, 1, 2, 3 },
        { 4, 5, 6, 7 },
        { 8, 9, 8, 7 }
    };
    learn::matrix<int> mx {
        { 0, 1, 2, 3 },
        { 4, 5, 6, 7 },
        { 8, 9, 8, 7 }
    };

    // Act
    // nothing

    // Assert
    ASSERT_EQ(mx.get_m(), 3);
    ASSERT_EQ(mx.get_n(), 4);
    for (size_t i = 0; i < expected_items.size(); i++)
        for (size_t j = 0; j < expected_items[0].size(); j++)
            ASSERT_EQ(mx.at(i, j), expected_items[i][j]);
}

TEST(matrix_test, size) {
    // Arrange
    learn::matrix<int> mx(3, 5);

    // Act
    // nothing

    // Assert
    EXPECT_EQ(mx.get_m(), 3);
    EXPECT_EQ(mx.get_n(), 5);
    
    auto [lines, columns] = mx.get_size();
    EXPECT_EQ(lines, 3);
    EXPECT_EQ(columns, 5);

    ASSERT_FALSE(mx.is_square());
}

TEST(matrix_test, transpose_square) {
    // Arrange
    learn::matrix<int> mx {
        { 0, 1, 2 },
        { 3, 4, 5 },
        { 6, 7, 8 },
    };
    learn::matrix<int> expected_mx {
        { 0, 3, 6 },
        { 1, 4, 7 },
        { 2, 5, 8 },
    };

    // Act
    // nothing

    // Assert
    ASSERT_EQ(mx.get_m(), expected_mx.get_m());
    ASSERT_EQ(mx.get_n(), expected_mx.get_n());
    ASSERT_EQ(mx.transpose(), expected_mx);
}

TEST(matrix_test, transpose_non_square) {
    // Arrange
    learn::matrix<int> mx {
        { 0, 1, 2, 3 },
        { 4, 5, 6, 7 },
        { 8, 9, 0, 1 },
    };
    learn::matrix<int> expected_mx {
        { 0, 4, 8 },
        { 1, 5, 9 },
        { 2, 6, 0 },
        { 3, 7, 1 }
    };

    // Act
    // nothing

    // Assert
    ASSERT_EQ(mx.get_m(), expected_mx.get_n());
    ASSERT_EQ(mx.get_n(), expected_mx.get_m());
    ASSERT_EQ(mx.transpose(), expected_mx);
}

TEST(matrix_test, minor) {
    // Arrange
    learn::matrix<int> mx {
        { 0, 1, 2 },
        { 3, 4, 5 },
        { 6, 7, 8 }
    };
    learn::matrix<int> expect_mx_1 {
        { 4, 5 },
        { 7, 8 }
    };
    learn::matrix<int> expect_mx_2 {
        { 3, 5 },
        { 6, 8 }
    };
    learn::matrix<int> expect_mx_3 {
        { 0, 2 },
        { 6, 8 }
    };

    // Act
    // nothing

    // Assert
    ASSERT_EQ(mx.minor(0, 0), expect_mx_1);
    ASSERT_EQ(mx.minor(0, 1), expect_mx_2);
    ASSERT_EQ(mx.minor(1, 1), expect_mx_3);
}

TEST(matrix_test, equality) {
    // Arrange
    learn::matrix<int> mx {
        { 0, 1, 2 },
        { 3, 4, 5 }
    };
    learn::matrix<int> expected_mx {
        { 0, 1, 2 },
        { 3, 4, 5 }
    };

    // Act
    // nothing

    // Assert
    ASSERT_TRUE(mx == expected_mx);
    ASSERT_FALSE(mx != expected_mx);
}

/*
    
    Блок тестирования метода нахождения определитля матрицы

*/

class determinant_test : public testing::TestWithParam<std::pair<learn::matrix<int>, int>> {
    
};

TEST_P(determinant_test, det_test) {
    // Arrange
    auto [mx, exp_det] = GetParam();

    // Act
    // nothing

    // Assert
    ASSERT_TRUE(mx.is_square());

    ASSERT_EQ(mx.determinant(), exp_det);
}

INSTANTIATE_TEST_CASE_P(
    instantiate_det_test,
    determinant_test,
    testing::Values(
        std::pair(
            learn::matrix<int> { 
                { 1, 2 },
                { 3, 4 }
            },
            -2
        ),
        
        std::pair(
            learn::matrix<int> { 
                { 1, -2, 3 },
                { 4, 0, 6 },
                { -7, 8, 9 }
            },
            204
        ),
        
        std::pair(
            learn::matrix<int> { 
                { 3, 2, 1 },
                { 2, -1, 3 },
                { 1, 3, -4 }
            },
            14
        ),

        std::pair(
            learn::matrix<int> { 
                { 1, 2, 3, -2 },
                { 1, -1, -2, -3 },
                { 3, 2, -1, 2 },
                { 2, -3, 2, 1 }
            },
            288
        ),
        
        std::pair(
            learn::matrix<int> { 
                { 1, 2, 3, 4 },
                { 3, 4, 1, 2 },
                { 2, 3, 4, 1 },
                { 4, 1, 2, 3 }
            },
            -160
        )
    )
);

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}