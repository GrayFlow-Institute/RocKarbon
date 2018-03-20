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

static bool canRun{false}; // 原子型静态变量控制发现服务器线程执行，因为是单个，所以不用担心竞争

class DiscService::Impl {
public:

    Status status = Status::NOTINIT;
    string ip;
    unsigned short port;
    string name;
    string info;
    string code;

    LoggerBase *logger = nullptr;
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

    if (mImpl->logger != nullptr)mImpl->logger->debug("Service Init.");
    return true;
}

Status DiscService::getStatus() {
    return mImpl->status;
}

bool DiscService::down() {
    // 如果服务器状态不是 RUNNING 则打印 Log 并退出
    if (getStatus() != Status::RUNNING) {
        if (mImpl->logger != nullptr)mImpl->logger->warning("Service Not RUNNING.");
        return false;
    }
    mImpl->status = Status::STOP;
    canRun = false;

    if (mImpl->logger != nullptr)mImpl->logger->debug("Service Will Stop.");
    return true;
}

bool DiscService::run() {
    // 如果服务器状态不是 STOP 则打印 Log 并退出
    if (getStatus() != Status::STOP) {
        if (mImpl->logger != nullptr)mImpl->logger->warning("Service Not STOP.");
        return false;
    }
    mImpl->status = Status::RUNNING;
    canRun = true;

    // 一堆提示的 Log
    if (mImpl->logger != nullptr)mImpl->logger->debug("IP is " + mImpl->ip);
    if (mImpl->logger != nullptr)mImpl->logger->debug("Port is " + to_string(mImpl->port));
    if (mImpl->logger != nullptr)mImpl->logger->debug("Name is " + mImpl->name);
    if (mImpl->logger != nullptr)mImpl->logger->debug("Info is " + mImpl->info);
    if (mImpl->logger != nullptr)mImpl->logger->debug("Code is " + mImpl->code);

    if (mImpl->logger != nullptr)mImpl->logger->debug("Service Start.");

    DiscService::Impl pData = *mImpl;
    pData.logger = nullptr;

    thread t([pData] {
        // 初始化返回数据
        string returnData;
        returnData += "rockarbon/1.0\n";
        returnData += to_string(time(nullptr));
        returnData += pData.ip;
        returnData += to_string(pData.port);
        returnData += pData.name;
        returnData += pData.code;
        returnData += pData.info;

        // 服务器返回数据逻辑
        io_service service;
        udp::socket sock(service, udp::endpoint(udp::v4(), pData.port));
        while (true) {
            udp::endpoint sender_ep;
            if (!canRun) break;
            size_t bytes = sock.receive_from(buffer(returnData), sender_ep);
            if (bytes != 0) {
                sock.send_to(buffer(returnData), sender_ep);
            }
        }
    });
    t.detach();

    return true;
}

