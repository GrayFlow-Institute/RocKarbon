//
// Created by yanyuhl on 18-3-16.
//

#ifndef ROCKARBON_DATAEXC_H
#define ROCKARBON_DATAEXC_H

#include <string>

#include "ServerStatus.h"
#include "../system/Env.h"
#include "../interface/ServiceBase.h"

class DataExc : public ServiceBase {
public:
    DataExc();

    ~DataExc() override ;

    // APIs

    bool init(const Env &env) override;

    Status getStatus() override;

    void down() override;

    bool run() override;

private:
    class Impl; // 为了封装实现 :)

    Impl *mImpl;
};


#endif //ROCKARBON_DATAEXC_H
