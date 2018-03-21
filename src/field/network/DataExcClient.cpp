//
// Created by yanyuhl on 18-3-17.
//

#include "DataExcClient.h"
#include "../../interface/LoggerBase.h"
#include "../system/Env.h"
#include <boost/asio.hpp>
#include <utility>

using namespace std;
using boost::asio::buffer;
using boost::asio::ip::tcp;

class DataExcClient::Impl {
public:
    Status status = Status::NOTINIT;
    shared_ptr<tcp::socket> socket;
    string passwd;
    shared_ptr<LoggerBase> logger;

};

DataExcClient::DataExcClient() : mImpl(new DataExcClient::Impl()) {}

DataExcClient::~DataExcClient() { delete mImpl; }

bool DataExcClient::init(shared_ptr<tcp::socket> socket, string passwd) {
    // 如果客户端状态不是 NOTINIT 则打印 Log 并退出
    if (getStatus() != Status::NOTINIT) {
        if (mImpl->logger != nullptr)mImpl->logger->warning("Client Not NOTINIT");
        return false;
    }

    if (socket == nullptr) {
        return false;
    }

    Env &env = Env::getInstance();

    mImpl->passwd = move(passwd);
    mImpl->socket = socket;
    mImpl->logger.reset(env.getLogger("DataExcClient"));

    if (mImpl->logger != nullptr)mImpl->logger->debug("Client Init");
    mImpl->status = Status::RUNNING;
    return true;
}

bool DataExcClient::sendData(std::string data) {
    // 如果客户端状态不是 RUNNING 则打印 Log 并退出
    if (getStatus() != Status::RUNNING) {
        if (mImpl->logger != nullptr)mImpl->logger->warning("Client Not RUNNING");
        return false;
    }

    try {
        boost::system::error_code ignored_error;
        boost::asio::write(
                *mImpl->socket,
                buffer(data),
                boost::asio::transfer_all(),
                ignored_error
        );

    } catch (exception &e) {
        if (mImpl->logger != nullptr)mImpl->logger->debug(e.what());
        close();
        return false;
    }
    return true;
}

Status DataExcClient::getStatus() {
    return mImpl->status;
}

bool DataExcClient::close() {
    // 如果客户端状态不是 RUNNING 则打印 Log 并退出
    if (getStatus() != Status::RUNNING) {
        if (mImpl->logger != nullptr)mImpl->logger->warning("Client Not RUNNING");
        return false;
    }
    mImpl->status = Status::CLOSED;
    if (mImpl->logger != nullptr)mImpl->logger->debug("Client Will Close");
    return true;
}

bool DataExcClient::check() {
    //TODO
    return false;
}


