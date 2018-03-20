//
// Created by yanyuhl on 18-3-20.
//

#include <gtest/gtest.h>
#include "../../src/base/system/Env.h"

using namespace std;

TEST(System, Env) {
    Env &env = Env::getInstance();
    EXPECT_EQ(env.getData(StringEnv::InstanceOnlyCode), "");
    EXPECT_EQ(env.getData(NumberEnv::PORT), 0);

    EXPECT_EQ(env.putData(NumberEnv::PORT, 1234), true);
    EXPECT_EQ(env.putData(NumberEnv::PORT, 1234), false);

    EXPECT_EQ(env.putData(StringEnv::InstanceOnlyCode, "abcd1234"), true);
    EXPECT_EQ(env.putData(StringEnv::InstanceOnlyCode, "abcd1234"), false);

    EXPECT_EQ(env.getData(StringEnv::InstanceOnlyCode), "abcd1234");
    EXPECT_EQ(env.getData(NumberEnv::PORT), 1234);
}
