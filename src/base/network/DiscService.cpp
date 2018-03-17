//
// Created by yanyuhl on 18-3-15.
//

#include "DiscService.h"
#include "ServerStatus.h"

class DiscService::Impl {
public:
    // TODO 添加实现

};


DiscService::DiscService() : mImpl(new DiscService::Impl()) {};

DiscService::~DiscService() { delete (mImpl); }

bool DiscService::init(const Env &env) {
    return false;
}

Status DiscService::getStatus() {
    return Status::NOTINIT;
}

void DiscService::down() {

}

bool DiscService::run() {
    return false;
}
