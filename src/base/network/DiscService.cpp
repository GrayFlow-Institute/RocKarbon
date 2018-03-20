//
// Created by yanyuhl on 18-3-15.
//

#include <boost/asio.hpp>

#include "DiscService.h"
#include "ServerStatus.h"

using boost::asio::io_service;
using boost::asio::ip::udp;
using boost::asio::buffer;
using namespace std;

class DiscService::Impl {
public:
    Status status = Status::NOTINIT;
    string ip;
    int port;
    string name;
    string info;
    string code;

};


DiscService::DiscService() : mImpl(new DiscService::Impl()) {};

DiscService::~DiscService() { delete (mImpl); }

bool DiscService::init() {
    Env &env = Env::getInstance();

    string ip;
    int port;
    string name;
    string info;
    string code;

    if ((ip = env.getData(StringEnv::IP)).empty()) {
        return false;
    }

    if ((port = env.getData(NumberEnv::PORT)) == -1) {
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

    mImpl->ip = ip;
    mImpl->port = port;
    mImpl->name = name;
    mImpl->info = info;
    mImpl->code = code;

    mImpl->status = Status::STOP;
    return true;
}

Status DiscService::getStatus() {
    return mImpl->status;
}

void DiscService::down() {

}

bool DiscService::run() {
//
//
//    io_service service;
//
//    void handle_connections() {
//        char buff[1024];
//        udp::socket sock(service, udp::endpoint(udp::v4(), 8001));
//        while (true) {
//            udp::endpoint sender_ep;
//            int bytes = sock.receive_from(buffer(buff), sender_ep);
//            std::string msg(buff, bytes);
//            sock.send_to(buffer(msg), sender_ep);
//        }
//    }
//

    return false;
}
