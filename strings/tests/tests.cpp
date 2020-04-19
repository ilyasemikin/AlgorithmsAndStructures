#include <string>
#include <vector>
#include <iostream>
#include <gtest/gtest.h>
#include "string_split.hpp"

struct strings_split_params {
    std::string input;
    std::vector<std::string> expected;
};

template <typename T>
std::ostream &operator<<(std::ostream &str, const std::vector<T> &cont) {
    str << "{ ";
    for (size_t i = 0; i < cont.size(); i++) {
        str << cont[i];
        if (i != cont.size() - 1)
            str << ", ";
    }
    return str << " }";
}

std::ostream &operator<<(std::ostream &str, const strings_split_params &value) {
    return str << "{ " << value.input << ", " << value.expected << " }";
}

class strings_split_test : public testing::TestWithParam<strings_split_params> {

};

template <typename T>
void check_equil_vectors(std::vector<T> &lvl, std::vector<T> &rvl) {
    ASSERT_EQ(lvl.size(), rvl.size());
    for (size_t i = 0; i < lvl.size(); i++)
        ASSERT_EQ(lvl[i], rvl[i]);
}

TEST(strings_split, strings_split_empty) {
    std::string empty_string;

    auto words = learn::split_into_words(empty_string);

    ASSERT_TRUE(words.empty());
}

TEST_P(strings_split_test, strings_split) {
    auto values = GetParam();
    
    auto words = learn::split_into_words(values.input);

    check_equil_vectors(words, values.expected);
}

INSTANTIATE_TEST_CASE_P(
    instantiate_split_test,
    strings_split_test,
    testing::Values(
        strings_split_params{ "hello world",            { "hello", "world" } },
        strings_split_params{ " hello world",           { "hello", "world" } },
        strings_split_params{ "hello    world",         { "hello", "world" } },
        strings_split_params{ "  hello   world  ",      { "hello", "world" } }
    )
);

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}