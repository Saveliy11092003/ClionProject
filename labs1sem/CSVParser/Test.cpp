//
// Created by user on 24.12.22.
//
#include <iostream>
#include <utility>
#include "gtest/gtest.h"
#include "CsvParser_dir/Csv.h"

TEST(lab4_test, check_format) {
    string s;
    s.push_back(5);
    int digit = 5;
    ASSERT_EQ(5, format<decltype(digit)>(s));
}