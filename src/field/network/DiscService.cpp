//
// Created by yanyuhl on 18-3-15.
//

#include <boost/asio.hpp>
#include <thread>
#include <ctime>

#include "DiscService.h"
#include "ServerStatus.h"

constexpr int BUFF_SIZE = 1024;

using boost::asio::io_service;
using boost::asio::ip::udp;
using boost::asio::buffer;
using namespace std;

class DiscService::Impl {
public:

    Status status = Status::NOTINIT;
    string ip;
    unsigned short port;
    string name;
    string info;
    string code;
    bool canRun = false;
    LoggerBase *logger = nullptr;

    ~Impl() {
        delete (logger);
    }
};


DiscService::DiscService() : mImpl(new DiscService::Impl()) {};

DiscService::~DiscService() { delete (mImpl); }

bool DiscService::init() {
    // 如果服务器状态不是 NOTINIT 则退出
    if (getStatus() != Status::NOTINIT) {
        return false;
    }

    Env &env = Env::getInstance();

    string ip;
    int port;
    string name;
    string info;
    string code;

    // 校验环境变量值
    if ((ip = env.getData(StringEnv::IP)).empty()) {
        return false;
    }

    if ((port = env.getData(NumberEnv::PORT)) == -1 || port < 0 || port > USHRT_MAX) {
        return false;
    }

    if ((name = env.getData(StringEnv::SERVER_NAME)).empty()) {
        return false;
    }

    if ((info = env.getData(StringEnv::SERVER_INFO)).empty()) {
        return false;
    }

    if ((code = env.getData(StringEnv::INSTANCE_ONLY_CODE)).empty()) {
        return false;
    }

    // 初始化私有数据
    mImpl->logger = env.getLogger("DiscService");
    mImpl->ip = ip;
    mImpl->port = static_cast<unsigned short>(port);
    mImpl->name = name;
    mImpl->info = info;
    mImpl->code = code;

    mImpl->status = Status::STOP;

    if (mImpl->logger != nullptr)mImpl->logger->debug("Service Init");
    return true;
}

Status DiscService::getStatus() {
    return mImpl->status;
}

bool DiscService::down() {
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

bool DiscService::run() {
    // 如果服务器状态不是 STOP 则打印 Log 并退出
    if (getStatus() != Status::STOP) {
        if (mImpl->logger != nullptr)mImpl->logger->warning("Service Not STOP");
        return false;
    }
    mImpl->status = Status::RUNNING;
    mImpl->canRun = true;

    // 一堆提示的 Log
    if (mImpl->logger != nullptr)mImpl->logger->debug("IP is " + mImpl->ip);
    if (mImpl->logger != nullptr)mImpl->logger->debug("Port is " + to_string(mImpl->port));
    if (mImpl->logger != nullptr)mImpl->logger->debug("Name is " + mImpl->name);
    if (mImpl->logger != nullptr)mImpl->logger->debug("Info is " + mImpl->info);
    if (mImpl->logger != nullptr)mImpl->logger->debug("Code is " + mImpl->code);


    // 服务器返回数据逻辑
    io_service service;
    // 接收缓冲区
    char buff[BUFF_SIZE];

    string returnData;
    returnData += "rockarbon/1.0\n";
    returnData += to_string(time(nullptr)) + "\n";
    returnData += mImpl->code + "\n";
    returnData += mImpl->ip + "\n";
    returnData += to_string(mImpl->port) + "\n";
    returnData += mImpl->name + "\n";
    returnData += mImpl->info;

    if (mImpl->logger != nullptr)mImpl->logger->debug("Service Start");
    udp::socket sock(service, udp::endpoint(udp::v4(), mImpl->port));
    while (mImpl->canRun) {
        udp::endpoint sender_ep;
        memset(buff, 0, BUFF_SIZE);

        size_t bytes = sock.receive_from(buffer(buff), sender_ep);
        string sender_info = sender_ep.address().to_string() + ":" + to_string(sender_ep.port());
        if (mImpl->logger != nullptr)
            mImpl->logger->debug(
                    sender_info +
                    "\n\nData is:\n" +
                    buff + "\n");

        if (bytes != 0) {
            if (mImpl->logger != nullptr)mImpl->logger->debug("Send Data");
            sock.send_to(buffer(returnData), sender_ep);
        }
    }
    return true;
}



