//
// Created by user on 28.12.22.
//
#include <utility>
#include "gtest/gtest.h"
#include "CSVParser.h"

using namespace std;

TEST(MyTests, check_format_str) {
    string element = "dlfjal";
    string a = format<string>(element);

ASSERT_EQ(a, element);
}

TEST(MyTests, check_CSV) {
    ifstream file("/home/user/CLionProjects/lab4oop/file1");
    CSVParser<int, string, int> parser(file, 0 /*skip first lines count*/);
    for (tuple<int, string, int> rs : parser) {
        ASSERT_EQ(get<0>(rs), 3);
        ASSERT_EQ(get<1>(rs), "white");
        ASSERT_EQ(get<2>(rs), 3);
    }
}
