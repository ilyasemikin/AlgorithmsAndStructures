#include <gtest/gtest.h>
#include "stack.hpp"

template <typename T>
class stack_test : public testing::Test {

};

using item_type = int;

TYPED_TEST_CASE_P(stack_test);

TYPED_TEST_P(stack_test, empty_on_startup) {
    // Arrange
    TypeParam stack;

    // Act
    // nothing

    // Assert
    EXPECT_EQ(stack.count(), 0);
    ASSERT_TRUE(stack.empty());
}

TYPED_TEST_P(stack_test, pop_empty) {
    // Arrange
    TypeParam stack;

    // Act
    // nothing

    // Assert
    ASSERT_THROW(stack.pop(), std::logic_error);
}

TYPED_TEST_P(stack_test, front_and_back) {
    // Arrange
    TypeParam stack { 0, 1 };

    // Act
    // nothing

    // Assert
    EXPECT_EQ(stack.count(), 2);
    EXPECT_FALSE(stack.empty());
    EXPECT_EQ(stack.front(), 0);
}

TYPED_TEST_P(stack_test, push_and_pop) {
    // Arrange
    TypeParam stack;
    std::vector<item_type> items { 0, 1, 2, 3 };

    // Act
    for (size_t i = 0; i < items.size(); i++)
        stack.push(items[i]);
    
    // Assert
    ASSERT_EQ(stack.count(), 4);
    for (size_t i = 0; i < items.size(); i++) {
        EXPECT_EQ(stack.front(), items[items.size() - i - 1]);
        stack.pop();
        ASSERT_EQ(stack.count(), items.size() - i - 1);
    }
    ASSERT_TRUE(stack.empty());
}

REGISTER_TYPED_TEST_CASE_P(
    stack_test,
    empty_on_startup,
    pop_empty,
    front_and_back,
    push_and_pop
);

using stack_types = testing::Types<
    learn::stack<item_type>
>;

INSTANTIATE_TYPED_TEST_CASE_P(stack_instantiation, stack_test, stack_types);

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}