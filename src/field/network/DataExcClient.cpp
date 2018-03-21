//
// Created by yanyuhl on 18-3-17.
//

#include "DataExcClient.h"
#include "../../interface/LoggerBase.h"
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
    mImpl->passwd = move(passwd);
    mImpl->socket = socket;
    return true;
}

bool DataExcClient::sendData(std::string data) {
//    try {
//
//        boost::system::error_code ignored_error;
//        boost::asio::write(
//                mImpl->socket,
//                buffer(data),
//                boost::asio::transfer_all(),
//                ignored_error
//        );
//
//    } catch (exception &e) {
//
//        return false;
//    }
//    return true;
}

Status DataExcClient::getStatus() {
    return mImpl->status;
}

bool DataExcClient::close() {
    return false;
}

bool DataExcClient::check() {

    return false;
}


