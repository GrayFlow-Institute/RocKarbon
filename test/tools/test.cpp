//
// Created by yanyuhl on 18-3-20.
//

#include <iostream>
#include <gtest/gtest.h>
#include "../../src/base/tools/StringUtils.h"

using namespace std;

TEST(StringUtils, getRandomString) {
    StringUtils utils;
    EXPECT_EQ(utils.getRandomString("a", 6), "aaaaaa");
    EXPECT_EQ(utils.getRandomString(0), "");
    EXPECT_EQ(utils.getRandomString(-3), "");
    EXPECT_EQ(utils.getRandomString("", -3), "");
    EXPECT_EQ(utils.getRandomString("", 0), "");
}
