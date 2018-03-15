//
// Created by yanyuhl on 18-3-15.
//

#include "StorageFactory.h"
#include <mutex>

static std::mutex m;

StorageFactory &StorageFactory::getInstance() {
    std::lock_guard<std::mutex> locker(m);
    static StorageFactory factory;
    return factory;
}

StorageFactory::~StorageFactory() = default;

StorageFactory::StorageFactory() = default;

