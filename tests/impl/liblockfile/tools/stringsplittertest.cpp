#include "liblockfile/tools/stringsplitter.hpp"

#include <gtest/gtest.h>

namespace {

using namespace liblockfile::internal;

TEST(StringSplitterTest, SplitEmptyStringReturnsAnEmptyVector) {
    EXPECT_EQ(std::vector<std::string>(), StringSplitter().split("", ' '));
    EXPECT_EQ(std::vector<std::string>(), StringSplitter().split("", 'a'));
}

TEST(StringSplitterTest, SplitStringByNonPresentDelimiterReturnsTheString) {
    EXPECT_EQ(std::vector<std::string>{"abcd"}, StringSplitter().split("abcd", 'h'));
    EXPECT_EQ(std::vector<std::string>{"a,b,c,d"}, StringSplitter().split("a,b,c,d", '1'));
}

TEST(StringSplitterTest, SplitStringByDelimiterReturnsPartsOfTheString) {
    EXPECT_EQ((std::vector<std::string>{"1", "2", "3"}), StringSplitter().split("1,2,3", ','));
    EXPECT_EQ((std::vector<std::string>{"abc", "def", "ghi"}), StringSplitter().split("abc:def:ghi", ':'));
}

}