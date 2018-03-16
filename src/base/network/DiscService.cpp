//
// Created by yanyuhl on 18-3-15.
//

#include "DiscService.h"

class DiscService::Impl {
public:
    // TODO 添加实现

};


DiscService::DiscService() : mImpl(new DiscService::Impl()) {};

DiscService::~DiscService() { delete (mImpl); }