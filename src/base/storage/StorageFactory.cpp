//
// Created by yanyuhl on 18-3-15.
//

#include "StorageFactory.h"
#include "FileStorage.h"
#include <mutex>
#include <string>

using namespace std;

static mutex m;

StorageFactory &StorageFactory::getInstance() {
    lock_guard<mutex> locker(m);
    static StorageFactory factory;
    return factory;
}

StorageBase *StorageFactory::createStorage(StorageType type, string path) {
    StorageBase *storage = nullptr;
    if (type == StorageType::FILE) {
        storage = &FileStorage::getInstance();
        if (!storage->init(path))return nullptr;
    }
    return storage;
}

StorageFactory::~StorageFactory() = default;

StorageFactory::StorageFactory() = default;

