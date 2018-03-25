//
// Created by yanyuhl on 18-3-16.
//

#ifndef ROCKARBON_ClientBase_H
#define ROCKARBON_ClientBase_H


#include "ClientStatus.h"
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

    virtual bool recData(std::string &)=0;

    virtual bool sendAndRecData(std::string, std::string &)=0;

    virtual bool init(std::shared_ptr<boost::asio::ip::tcp::socket>, std::string passwd)=0;

    virtual Status getStatus()=0;

    virtual bool close()=0;

    virtual bool check()=0;
};


#endif //ROCKARBON_ClientBase_H
