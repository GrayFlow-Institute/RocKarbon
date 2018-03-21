//
// Created by yanyuhl on 18-3-16.
//

#include "DataExc.h"
#include "ServiceStatus.h"
#include <string>
#include <climits>
#include <memory>

using namespace std;

class DataExc::Impl {
public:
    Status status = Status::NOTINIT;
    string ip;
    unsigned short port;
    string passwd;
    bool canRun = false;
    shared_ptr<LoggerBase> logger;

//    ~Impl() {
//        delete (logger);
//    }

};

DataExc::DataExc() : mImpl(new DataExc::Impl()) {};

DataExc::~DataExc() { delete (mImpl); }

bool DataExc::init() {
    // 如果服务器状态不是 NOTINIT 则退出
    if (getStatus() != Status::NOTINIT) {
        return false;
    }

    Env &env = Env::getInstance();

    string ip;
    int port;
    string passwd;

    // 校验环境变量值
    if ((ip = env.getData(StringEnv::IP)).empty()) {
        return false;
    }

    if ((port = env.getData(NumberEnv::PORT)) == -1 || port < 0 || port > USHRT_MAX) {
        return false;
    }

    if ((passwd = env.getData(StringEnv::PASSWORD)).empty()) {
        return false;
    }

    // 初始化私有数据
    mImpl->logger.reset(env.getLogger("DataExc"));
    mImpl->ip = ip;
    mImpl->port = static_cast<unsigned short>(port);
    mImpl->passwd = passwd;

    mImpl->status = Status::STOP;

    if (mImpl->logger != nullptr)mImpl->logger->debug("Service Init");
    return true;
}

Status DataExc::getStatus() {
    return mImpl->status;
}

bool DataExc::down() {
    // 如果服务器状态不是 RUNNING 则打印 Log 并退出
    if (getStatus() != Status::RUNNING) {
        if (mImpl->logger != nullptr)mImpl->logger->warning("Service Not RUNNING");
        return false;
    }
    mImpl->status = Status::STOP;
    mImpl->canRun = false;

    if (mImpl->logger != nullptr)mImpl->logger->debug("Service Will Stop");
    return true;
}

bool DataExc::run() {
    // 如果服务器状态不是 STOP 则打印 Log 并退出
    if (getStatus() != Status::STOP) {
        if (mImpl->logger != nullptr)mImpl->logger->warning("Service Not STOP");
        return false;
    }
    mImpl->status = Status::RUNNING;
    mImpl->canRun = true;


    // TODO 服务器逻辑

    return true;
}
