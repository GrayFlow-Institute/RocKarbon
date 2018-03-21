//
// Created by yanyuhl on 18-3-17.
//

#include "Client.h"

class Client::Impl {
public:
    // TODO 添加实现
};


Client::Client() : mImpl(new Client::Impl()) {};

Client::~Client() { delete (mImpl); }
