//
// Created by yanyuhl on 18-3-21.
//


#include <gtest/gtest.h>
#include <memory>
#include "../../src/field/network/DiscService.h"
#include "../../src/field/network/DataExcService.h"
#include "../../src/field/system/Env.h"

using namespace std;

TEST(Network, DiscService) {
    Env &env = Env::getInstance();
    shared_ptr<ServiceBase> ds(new DiscService());

    EXPECT_EQ(ds->init(), false);

    env.putData(StringEnv::IP, "127.0.0.1");
    env.putData(StringEnv::INSTANCE_ONLY_CODE, "ABCD1234");
    env.putData(StringEnv::SERVER_NAME, "测试服");
    env.putData(StringEnv::SERVER_INFO, "测试信息");

    env.putData(NumberEnv::PORT, 23333);
    env.putData(NumberEnv::LOGGER, static_cast<int>(LoggerType::RELEASE));

    EXPECT_EQ(ds->getStatus(), Status::NOTINIT);
    EXPECT_EQ(ds->run(), false);
    EXPECT_EQ(ds->down(), false);
    EXPECT_EQ(ds->init(), true);
    EXPECT_EQ(ds->getStatus(), Status::STOP);
    EXPECT_EQ(ds->down(), false);

}


TEST(Network, DataExc) {
    Env &env = Env::getInstance();
    shared_ptr<ServiceBase> de(new DataExcService());

    EXPECT_EQ(de->init(), false);

    env.putData(StringEnv::PASSWORD, "123456");

    env.putData(NumberEnv::PORT, 23333);

    EXPECT_EQ(de->getStatus(), Status::NOTINIT);
    EXPECT_EQ(de->run(), false);
    EXPECT_EQ(de->down(), false);
    EXPECT_EQ(de->init(), true);
    EXPECT_EQ(de->getStatus(), Status::STOP);
    EXPECT_EQ(de->down(), false);
}