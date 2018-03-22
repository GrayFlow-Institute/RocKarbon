//
// Created by yanyuhl on 18-3-21.
//


#include <gtest/gtest.h>
#include <memory>
#include <boost/asio.hpp>

#include "../../src/interface/ServiceBase.h"
#include "../../src/interface/ClientBase.h"
#include "../../src/field/network/DiscService.h"
#include "../../src/field/network/DataExcClient.h"
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

    env.clear();
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

    env.clear();
}

TEST(Network, DataExcClient) {
    Env &env = Env::getInstance();
    shared_ptr<ClientBase> dec(new DataExcClient());
    shared_ptr<boost::asio::ip::tcp::socket> socket;

    env.putData(NumberEnv::STORAGE, (int) StorageType::FILE);
    env.putData(StringEnv::STORAGE_PATH, "./test.dat");
//    env.putData(NumberEnv::LOGGER, (int) LoggerType::DEBUG);

    string passwd;

    boost::asio::io_service service;
    EXPECT_EQ(dec->init(socket, passwd), false);

    socket.reset(new boost::asio::ip::tcp::socket(service));
    EXPECT_EQ(dec->init(socket, passwd), true);
    EXPECT_EQ(dec->init(socket, passwd), false);
    EXPECT_EQ(dec->close(), false);

    env.clear();
}