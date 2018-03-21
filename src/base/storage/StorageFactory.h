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

    StorageBase *createStorage(StorageType type, std::string data);


private:
    StorageFactory();

    ~StorageFactory();

    StorageFactory(const StorageFactory &);

    const StorageFactory &operator=(const StorageFactory &);
};


#endif //ROCKARBON_STORAGEFACTORY_H
