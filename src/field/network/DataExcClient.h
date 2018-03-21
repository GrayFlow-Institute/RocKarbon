//
// Created by yanyuhl on 18-3-17.
//

#ifndef ROCKARBON_CLIENT_H
#define ROCKARBON_CLIENT_H

#include "ServiceStatus.h"
#include "../interface/ClientBase.h"
#include <string>

class DataExcClient : public ClientBase {
public:
    DataExcClient();

    ~DataExcClient();

    // APIs
    bool init(boost::asio::ip::tcp::socket socket) override;

    bool sendData(std::string data) override;

    Status getStatus() override;

    bool down() override;

    bool run() override;

private:
    class Impl; // 为了封装实现 :)

    Impl *mImpl;

};


#endif //ROCKARBON_CLIENT_H
