//
// Created by yanyuhl on 18-3-14.
//
#include "base/system/Env.h"
#include "base/tools/StringUtils.h"
#include "base/log/LoggerType.h"
#include "base/network/DiscService.h"

int main(int argc, char **argv) {
    Env &env = Env::getInstance();
    StringUtils utils;


    env.putData(StringEnv::IP, "127.0.0.1");
    env.putData(StringEnv::INSTANCE_ONLY_CODE, utils.getRandomString(32));
    env.putData(StringEnv::SERVER_NAME, "测试服");
    env.putData(StringEnv::SERVER_INFO, "测试信息");

    env.putData(NumberEnv::PORT, 23333);
    env.putData(NumberEnv::LOGGER, static_cast<int>(LoggerType::DEBUG));

    DiscService ds;
    ds.init();
    ds.run();
    ds.down();
}