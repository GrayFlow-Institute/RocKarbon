//
// Created by yanyuhl on 18-3-17.
//

#include "DataExcClient.h"
#include "../../interface/LoggerBase.h"
#include "../../interface/StorageBase.h"
#include "../../base/security/AESGuard.h"
#include "../system/Env.h"
#include <boost/asio.hpp>
#include <utility>

using namespace std;
using boost::asio::buffer;
using boost::asio::ip::tcp;

class DataExcClient::Impl {
public:
    Status status = Status::NOTINIT;
    shared_ptr<AESGuard> aes;
    shared_ptr<LoggerBase> logger;
    shared_ptr<StorageBase> storage;
    shared_ptr<tcp::socket> socket;
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
    mImpl->logger.reset(env.getLogger("DataExcClient"));
    mImpl->storage.reset(env.getStorage());

    if (mImpl->storage == nullptr) {
        if (mImpl->logger != nullptr)mImpl->logger->error("Storage Init Error");
        return false;
    }

    mImpl->aes.reset(new AESGuard());
    mImpl->aes->init(passwd);

    mImpl->socket = socket;
    if (mImpl->logger != nullptr)mImpl->logger->debug("Client Init");

    mImpl->status = Status::SYNCING;

    // TODO 同步


    mImpl->status = Status::SYNCED;
    return true;
}

bool DataExcClient::sendData(std::string data, string &reData) {
    // 如果客户端状态不是 SYNCED 或者 SYNCING ，则打印 Log 并退出
    if (getStatus() != Status::SYNCED || getStatus() == Status::SYNCING) {
        if (mImpl->logger != nullptr)mImpl->logger->warning("Client's Can't Send");
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
        boost::asio::read(
                *mImpl->socket,
                buffer(reData),
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
    // 如果客户端状态不是 SYNCED 则打印 Log 并退出
    if (getStatus() != Status::SYNCED || getStatus() != Status::SYNCING) {
        if (mImpl->logger != nullptr)mImpl->logger->warning("Client Not SYNCED");
        return false;
    }
    mImpl->status = Status::CLOSED;
    if (mImpl->logger != nullptr)mImpl->logger->debug("Client Will Close");
    return true;
}

bool DataExcClient::check() {
    if (getStatus() != Status::SYNCED) {
        if (mImpl->logger != nullptr)mImpl->logger->debug("Status Not SYNCED");
        return false;
    }

    string data = "rockarbon/1.0\nH\n";
    string redata;
    if (!sendData(data, redata)) {
        close();
        return false;
    } else {
        if (redata != "rockarbon/1.0\nR\n") {
            close();
            return false;
        } else {
            return true;
        }
    }
}


