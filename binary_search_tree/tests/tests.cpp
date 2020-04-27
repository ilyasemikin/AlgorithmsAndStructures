#include <gtest/gtest.h>
#include <vector>
#include <set>
#include "binary_search_tree.hpp"

TEST(binary_search_tree, empty_tree_on_startup) {
    learn::binary_search_tree<int> tree;

    ASSERT_TRUE(tree.empty());
    ASSERT_EQ(tree.size(), 0);
}

class bst_begin_test : public testing::TestWithParam<std::vector<int>> {

};

TEST_P(bst_begin_test, tree_begin) {
    learn::binary_search_tree<int> tree;
    auto values = GetParam();
    std::multiset<int> expected(values.begin(), values.end());

    for (const auto &item : values)
        tree.insert(item);

    auto res_it = tree.begin();

    for (const auto &value : values) {
        auto item = *res_it;
        res_it++;
        ASSERT_EQ(item, value);
    }
}

INSTANTIATE_TEST_CASE_P(
    instantiate_bst_begin_test,
    bst_begin_test,
    testing::Values(
        std::vector<int>{ 1, 4, 5, 0, 2 },
        std::vector<int>{ -3, 4, 5, 7 },
        std::vector<int>{ 5, 1, 4, -3 }
    )
);

int main(int args, char **argv) {
    testing::InitGoogleTest(&args, argv);
    return RUN_ALL_TESTS();
}