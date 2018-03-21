//
// Created by yanyuhl on 18-3-16.
//

#ifndef ROCKARBON_DATAEXC_H
#define ROCKARBON_DATAEXC_H

#include <string>

#include "../../interface/ServiceBase.h"
#include "../../interface/ServerStatus.h"
#include "../../field/system/Env.h"

class DataExcService : public ServiceBase {
public:
    DataExcService();

    ~DataExcService() override;

    // APIs

    bool init() override;

    Status getStatus() override;

    bool down() override;

    bool run() override;

private:
    class Impl; // 为了封装实现 :)

    Impl *mImpl;
};


#endif //ROCKARBON_DATAEXC_H
