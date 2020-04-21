#include <string>
#include <vector>
#include <iostream>
#include <gtest/gtest.h>
#include "string_split.hpp"
#include "prefix.hpp"
#include "string_find.hpp"

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

TEST_P(strings_split_test, strings_split) {
    auto values = GetParam();
    
    auto words = learn::split_into_words(values.input);

    ASSERT_EQ(words, values.expected);
}

INSTANTIATE_TEST_CASE_P(
    instantiate_split_test,
    strings_split_test,
    testing::Values(
        strings_split_params{ "",                       {} },
        strings_split_params{ "hello world",            { "hello", "world" } },
        strings_split_params{ " hello world",           { "hello", "world" } },
        strings_split_params{ "hello    world",         { "hello", "world" } },
        strings_split_params{ "  hello   world  ",      { "hello", "world" } }
    )
);

struct prefix_test_params {
    std::string input;
    std::vector<size_t> expected;
};

std::ostream &operator<<(std::ostream &str, const prefix_test_params &value) {
    return str << "{ " << value.input << ", " << value.expected << " }";
}

class prefix_test : public testing::TestWithParam<prefix_test_params> {

};

TEST_P(prefix_test, prefix) {
    auto values = GetParam();

    auto prefixs = learn::prefix_function(values.input);

    ASSERT_EQ(prefixs, values.expected);
}

INSTANTIATE_TEST_CASE_P(
    instantiate_prefix_test,
    prefix_test,
    testing::Values(
        prefix_test_params{ "", {} },
        prefix_test_params{ "abcabcd", std::vector<size_t>{ 0, 0, 0, 1, 2, 3, 0 } }
    )
);

struct find_substr_test_params {
    std::string str;
    std::string substr;
    size_t expected;
};

std::ostream &operator<<(std::ostream &str, const find_substr_test_params &value) {
    return str << "{ str = " << value.str 
               << ", substr = " << value.substr 
               << ", expected = " << value.expected << " }";
}

class find_substr_test : public testing::TestWithParam<find_substr_test_params> {

};

TEST_P(find_substr_test, find_substr) {
    auto values = GetParam();

    auto position = learn::find_substr(values.str, values.substr);

    ASSERT_EQ(position, values.expected);
}

INSTANTIATE_TEST_CASE_P(
    instantiate_find_substr_test,
    find_substr_test,
    testing::Values(
        find_substr_test_params{ "",                "hello",    std::string_view::npos },
        find_substr_test_params{ "hello",           "",         std::string_view::npos },
        find_substr_test_params{ "hello world",     "hello",    0 },
        find_substr_test_params{ "hello world",     "world",    6 },
        find_substr_test_params{ "hello world",     "friend",   std::string_view::npos }
    )
);

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}