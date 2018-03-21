//
// Created by yanyuhl on 18-3-16.
//

#ifndef ROCKARBON_DATAEXC_H
#define ROCKARBON_DATAEXC_H

#include <string>

#include "ServiceStatus.h"
#include "../../field/system/Env.h"
#include "../interface/ServiceBase.h"

class DataExc : public ServiceBase {
public:
    DataExc();

    ~DataExc() override;

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
