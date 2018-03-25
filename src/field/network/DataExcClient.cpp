//
// Created by yanyuhl on 18-3-17.
//

#include "DataExcClient.h"
#include "../../interface/LoggerBase.h"
#include "../../interface/StorageBase.h"
#include "../../interface/rockarbon_protocol.h"
#include "../../base/security/AESGuard.h"
#include "../system/Env.h"

using namespace std;
using boost::asio::buffer;
using boost::asio::ip::tcp;
using rockarbon::protocol::PROT_HEARBEAT_REQ;
using rockarbon::protocol::PROT_HEARBEAT_RES;
using rockarbon::protocol::PROT_SYNC_FIRST;
using rockarbon::protocol::PROT_SYNC_MORE;
using rockarbon::protocol::PROT_SYNC_DONE;

constexpr int BUFF_SIZE = 2048;

class DataExcClient::Impl {
public:
    Status status = Status::NOTINIT;
    StorageBase *storage; // 单例不能使用 shared_ptr
    shared_ptr<AESGuard> aes;
    shared_ptr<LoggerBase> logger;
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
    mImpl->storage = env.getStorage();
    if (mImpl->storage == nullptr) {
        if (mImpl->logger != nullptr)mImpl->logger->error("Storage Init Error");
        return false;
    }

    mImpl->aes.reset(new AESGuard());
    mImpl->aes->init(passwd);

    mImpl->socket = socket;
    if (mImpl->logger != nullptr)mImpl->logger->debug("Client Init");

    mImpl->status = Status::SYNCING;

    // 同步操作开始
    string reData;

    // 发送第一次请求
    if (!sendData(PROT_SYNC_FIRST, reData)) {
        close();
        return false;
    };

    reData = mImpl->storage->deal(reData);

    // 循环同步客户端，直到结束
    while (reData == "more") {
        if (!sendData(PROT_SYNC_MORE, reData)) {
            close();
            return false;
        }
        reData = mImpl->storage->deal(reData);
    }

    // 出现错误，直接关闭，并等待回收
    if (reData == "error") {
        close();
        return false;
    }

    // 返回服务器多出的数据
    if (!sendData(reData, reData)) {
        close();
        return false;
    }

    // 同步结束
    if (!sendData(PROT_SYNC_DONE, reData)) {
        close();
        return false;
    }
    mImpl->status = Status::SYNCED;
    return true;
}

/* *
 * 发送数据，并接受返回
 *
 * 发送格式：xxxxx\0
 * 接收格式：xxxxx\0
 *
 * */

bool DataExcClient::sendData(std::string data, string &reData) {
    // 如果客户端状态不是 SYNCED 或者 SYNCING ，则打印 Log 并退出
    if (getStatus() != Status::SYNCED || getStatus() == Status::SYNCING) {
        if (mImpl->logger != nullptr)mImpl->logger->warning("Client's Can't Send");
        return false;
    }

    mImpl->aes->decode(data);

    // 出现错误抛出异常
    try {
        boost::asio::write(
                *mImpl->socket,
                buffer(data, (data.size() + 1))
        );
        boost::asio::streambuf reDataBuf;
        boost::asio::read_until(*mImpl->socket, reDataBuf, "\0");
        reData.clear();
        std::istream(&reDataBuf) >> reData;
    } catch (exception &e) {
        if (mImpl->logger != nullptr)mImpl->logger->debug(e.what());
        close();
        return false;
    }

    // TODO 解密操作
    mImpl->aes->decode(reData);


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

    string redata;
    if (!sendData(PROT_HEARBEAT_REQ, redata)) {
        close();
        return false;
    } else {
        if (redata != PROT_HEARBEAT_RES) {
            close();
            return false;
        } else {
            return true;
        }
    }
}


