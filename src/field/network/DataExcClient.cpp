//
// Created by yanyuhl on 18-3-17.
//

#include "DataExcClient.h"
#include "../../base/interface/LoggerBase.h"

using namespace std;
using namespace boost::asio::ip;

class DataExcClient::Impl {
public:
    Status status = Status::NOTINIT;
    tcp::socket socket;
    string passwd;
    bool canRun = false;
    shared_ptr<LoggerBase> logger;

};

