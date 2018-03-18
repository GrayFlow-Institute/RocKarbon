//
// Created by yanyuhl on 18-3-15.
//

#ifndef ROCKARBON_STORAGEFACTORY_H
#define ROCKARBON_STORAGEFACTORY_H

#include <string>
#include "../interface/StorageBase.h"
#include "StorageType.h"

class StorageFactory {
public:
    static StorageFactory &getInstance();

    // TODO 添加实现
    StorageBase *createStorage(StorageType type);


private:
    StorageFactory();

    ~StorageFactory();

    StorageFactory(const StorageFactory &);

    const StorageFactory &operator=(const StorageFactory &);
};


#endif //ROCKARBON_STORAGEFACTORY_H
