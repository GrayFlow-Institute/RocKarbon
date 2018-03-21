//
// Created by yanyuhl on 18-3-17.
//

#ifndef ROCKARBON_CLIENT_H
#define ROCKARBON_CLIENT_H

#include "ClientStatus.h"
#include "ClientBase.h"
#include <string>

class DataExcClient : public ClientBase {
public:
    DataExcClient();

    ~DataExcClient() override;

    // APIs
    bool init(boost::asio::ip::tcp::socket &&socket,std::string passwd) override;

    bool sendData(std::string data) override;

    bool close() override;

    bool check() override;

    Status getStatus() override;

private:
    class Impl; // 为了封装实现 :)

    Impl *mImpl;

};


#endif //ROCKARBON_CLIENT_H
