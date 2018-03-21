//
// Created by yanyuhl on 18-3-17.
//

#ifndef ROCKARBON_CLIENT_H
#define ROCKARBON_CLIENT_H

#include "ServerStatus.h"
#include <boost/asio.hpp>
#include <string>

class Client {
public:
    Client();

    ~Client();

    // 客户端无法复制
    Client(const Client &other) = delete;

    Client &operator=(const Client &other)= delete;

    // APIs
    // TODO 添加实现

    bool init(boost::asio::ip::tcp::socket socket);

    void sendData(std::string data);

    Status getStatus();

    void down();

    bool run();

private:
    class Impl; // 为了封装实现 :)

    Impl *mImpl;

};


#endif //ROCKARBON_CLIENT_H
