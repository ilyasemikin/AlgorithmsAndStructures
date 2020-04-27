#include <gtest/gtest.h>
#include <vector>
#include <iostream>
#include <set>
#include "binary_search_tree.hpp"

TEST(binary_search_tree, empty_tree_on_startup) {
    learn::binary_search_tree<int> tree;

    ASSERT_TRUE(tree.empty());
    ASSERT_EQ(tree.size(), 0);
}

struct bst_test_params {
    std::vector<int> values;
    int min;
    int max;
};

template <typename T>
std::ostream &operator<<(std::ostream &str, const std::vector<T> &vec) {
    str << "{ ";
    bool first = true;

    for (auto item : vec) {
        if (!first)
            str << ", ";
        first = false;

        str << item;
    }
    return str;
}

std::ostream &operator<<(std::ostream &str, const bst_test_params &rhs) {
    return str << "{ " << rhs.values << ", min = " << rhs.min << ", max = " << rhs.max << " }";
}

class bst_test : public testing::TestWithParam<bst_test_params> {

};

TEST_P(bst_test, tree_begin) {
    learn::binary_search_tree<int> tree;
    auto params = GetParam();
    std::multiset<int> expected(params.values.begin(), params.values.end());

    for (const auto &item : params.values)
        tree.insert(item);

    auto min = tree.min();
    auto max = tree.max();

    ASSERT_EQ(min, params.min);
    ASSERT_EQ(max, params.max);
}

INSTANTIATE_TEST_CASE_P(
    instantiate_bst_test,
    bst_test,
    testing::Values(
        bst_test_params{ { 1, 4, 5, 0, 2 }, 0, 5 },
        bst_test_params{ { -3, 4, 5, 7 }, -3, 7 },
        bst_test_params{ { 5, 1, 4, -3 }, -3, 5 }
    )
);

int main(int args, char **argv) {
    testing::InitGoogleTest(&args, argv);
    return RUN_ALL_TESTS();
}