//
// Created by yanyuhl on 18-3-16.
//

#include "DataExcService.h"
#include "ServerStatus.h"
#include "DataExcClient.h"
#include <string>
#include <climits>
#include <thread>
#include <vector>
#include <boost/asio.hpp>

using namespace std;
using namespace boost::asio;
using namespace boost::system;


class DataExcService::Impl {
public:
    Status status = Status::NOTINIT;
    unsigned short port;
    string password;
    bool canRun = false;
    shared_ptr<LoggerBase> logger;
//    vector<shared_ptr<DataExcClient>> clients;
};

DataExcService::DataExcService() : mImpl(new DataExcService::Impl()) {};

DataExcService::~DataExcService() {}

bool DataExcService::init() {
    // 如果服务器状态不是 NOTINIT 则退出
    if (getStatus() != Status::NOTINIT) {
        return false;
    }

    Env &env = Env::getInstance();

    int port;
    string password;

    // 校验环境变量值

    if ((port = env.getData(NumberEnv::PORT)) == -1 || port < 0 || port > USHRT_MAX) {
        return false;
    }

    // 初始化私有数据
    mImpl->logger.reset(env.getLogger("DataExcService"));
    mImpl->port = static_cast<unsigned short>(port);
    mImpl->password = password;

    mImpl->status = Status::STOP;

    if (mImpl->logger != nullptr)mImpl->logger->debug("Service Init");
    return true;
}

Status DataExcService::getStatus() {
    return mImpl->status;
}

bool DataExcService::down() {
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

bool DataExcService::run() {
    // 如果服务器状态不是 STOP 则打印 Log 并退出
    if (getStatus() != Status::STOP) {
        if (mImpl->logger != nullptr)mImpl->logger->warning("Service Not STOP");
        return false;
    }
    mImpl->status = Status::RUNNING;
    mImpl->canRun = true;

    try {
        io_service service;

        ip::tcp::acceptor acceptor(service, ip::tcp::endpoint(ip::tcp::v4(), mImpl->port));
        while (mImpl->canRun) {
            shared_ptr<ip::tcp::socket> socket(new ip::tcp::socket(service));
            acceptor.accept(*socket);

            // 校验步骤在客户端实现

            shared_ptr<DataExcClient> client(new DataExcClient());

            thread t([this, socket, client] {
                bool status = client->init(socket, mImpl->password);
                if (mImpl->logger != nullptr)mImpl->logger->debug(status ? "Sync Finished" : "Sync Error");
            });
            t.detach();
//            mImpl->clients.insert(mImpl->clients.end(), client);
        }
    }
    catch (exception &e) {
        if (mImpl->logger != nullptr)mImpl->logger->debug(e.what());
        down();
        return false;
    }


    return true;
}

