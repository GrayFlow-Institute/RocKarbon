//
// Created by yanyuhl on 18-3-16.
//

#include "DataExc.h"
#include "ServerStatus.h"

class DataExc::Impl {
public:
    // TODO 添加实现

};


DataExc::DataExc() : mImpl(new DataExc::Impl()) {};

DataExc::~DataExc() { delete (mImpl); }

bool DataExc::init() {
    return false;
}

Status DataExc::getStatus() {
    return Status::NOTINIT;
}

bool DataExc::down() {

}

bool DataExc::run() {
    return false;
}
