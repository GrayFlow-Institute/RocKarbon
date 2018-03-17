//
// Created by yanyuhl on 18-3-15.
//

#ifndef ROCKARBON_DISCSERVICE_H
#define ROCKARBON_DISCSERVICE_H

#include <string>

#include "ServerStatus.h"
#include "../system/Env.h"
#include "../interface/ServiceBase.h"

class DiscService : public ServiceBase {
public:
    DiscService();

    ~DiscService() override;

    // APIs
    // TODO

    bool init(const Env &env) override;

    Status getStatus() override;

    void down() override;

    bool run() override;

private:
    class Impl; // 为了封装实现 :)

    Impl *mImpl;
};


#endif //ROCKARBON_DISCSERVICE_H
