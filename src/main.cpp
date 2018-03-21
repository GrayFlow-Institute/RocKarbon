//
// Created by yanyuhl on 18-3-14.
//
#include <thread>
#include "base/system/Env.h"
#include "base/tools/StringUtils.h"
#include "base/log/LoggerType.h"
#include "field/network/DiscService.h"

using namespace std;

int main(int argc, char **argv) {
    Env &env = Env::getInstance();
    LoggerBase* mainlog;
    StringUtils utils;


    env.putData(StringEnv::IP, "127.0.0.1");
    env.putData(StringEnv::INSTANCE_ONLY_CODE, utils.getRandomString(32));
    env.putData(StringEnv::SERVER_NAME, "测试服");
    env.putData(StringEnv::SERVER_INFO, "测试信息");

    env.putData(NumberEnv::PORT, 23333);
    env.putData(NumberEnv::LOGGER, static_cast<int>(LoggerType::DEBUG));


    mainlog=env.getLogger("main");

    DiscService ds;
    ds.init();

    thread t([&ds] {
        ds.run();
    });

    this_thread::sleep_for(std::chrono::milliseconds(1));
    ds.down();

    mainlog->debug("ds is down.now join.");
    t.join();
}