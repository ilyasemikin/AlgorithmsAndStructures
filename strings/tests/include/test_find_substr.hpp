#pragma once

#include <ostream>
#include <string>
#include <gtest/gtest.h>
#include <string_find_substr.hpp>

struct find_substr_parametrs {
    std::string str;
    std::string substr;
    size_t exp_value;
};

std::ostream &operator<<(std::ostream &str, const find_substr_parametrs &rhs) {
    return str << "{ str = \"" << rhs.str 
               << "\", substr = \"" << rhs.substr
               << "\", index = " << rhs.exp_value
               << "}";
}

class find_substr_test : public testing::TestWithParam<find_substr_parametrs> {

};

TEST_P(find_substr_test, kmp_test) {
    auto [str, substr, exp_value] = GetParam();

    auto value = learn::find_substr::KMP(str, substr);
    ASSERT_EQ(exp_value, value);
}

TEST_P(find_substr_test, bmh_test) {
    auto [str, substr, exp_value] = GetParam();

    auto value = learn::find_substr::BMH(str, substr);
    ASSERT_EQ(exp_value, value);
}

INSTANTIATE_TEST_CASE_P(
    inst_find_substr_test,
    find_substr_test,
    testing::Values(
        find_substr_parametrs{ "hello world yep", "world", 6 },
        find_substr_parametrs{ "world", "world", 0 },
        find_substr_parametrs{ "hello world yep", "yep", 12 },
        find_substr_parametrs{ "hello world yep", "what", learn::find_substr::not_found }
    )
);