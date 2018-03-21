//
// Created by yanyuhl on 18-3-16.
//

#ifndef ROCKARBON_ClientBase_H
#define ROCKARBON_ClientBase_H


#include "../network/ServiceStatus.h"
#include <boost/asio.hpp>
#include <string>

class ClientBase {
public:
    ClientBase() = default;

    virtual ~ClientBase() = default;

    // 客户端无法复制
    ClientBase(const ClientBase &other) = delete;

    ClientBase &operator=(const ClientBase &other)= delete;

    // APIs
    virtual bool sendData(std::string)=0;

    virtual bool init(boost::asio::ip::tcp::socket socket)=0;

    virtual Status getStatus()=0;

    virtual bool down()=0;

    virtual bool run()=0;
};


#endif //ROCKARBON_ClientBase_H
