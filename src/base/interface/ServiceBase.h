//
// Created by yanyuhl on 18-3-16.
//

#ifndef ROCKARBON_SERVICEBASE_H
#define ROCKARBON_SERVICEBASE_H


#include "../system/Env.h"
#include "../network/ServerStatus.h"

class ServiceBase {
public:

    // 服务器地址唯一，所以禁止复制

    ServiceBase() = default;

    virtual ~ServiceBase() = default;

    ServiceBase(const ServiceBase &) = delete;

    const ServiceBase &operator=(const ServiceBase &)= delete;

    // APIs

    virtual bool init(const Env &env)=0;

    virtual Status getStatus()=0;

    virtual void down()=0;

    virtual bool run()=0;
};

#endif //ROCKARBON_SERVICEBASE_H
