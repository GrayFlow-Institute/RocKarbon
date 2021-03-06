//
// Created by yanyuhl on 18-3-17.
//

#ifndef ROCKARBON_CLIENT_H
#define ROCKARBON_CLIENT_H

#include "../../interface/ClientStatus.h"
#include "../../interface/ClientBase.h"
#include <string>
#include <memory>

class DataExcClient : public ClientBase {
public:
    DataExcClient();

    ~DataExcClient() override;

    // APIs
    bool init(std::shared_ptr<boost::asio::ip::tcp::socket> socket, std::string passwd) override;

    bool sendData(std::string data);

    bool recData(std::string &reData);

    bool sendAndRecData(std::string data, std::string &reData) override;

    bool close() override;

    bool check() override;

    Status getStatus() override;

private:
    class Impl; // 为了封装实现 :)

    Impl *mImpl;

};


#endif //ROCKARBON_CLIENT_H
