//
// Created by yanyuhl on 18-3-15.
//

#ifndef ROCKARBON_STORAGEFACTORY_H
#define ROCKARBON_STORAGEFACTORY_H

#include <string>
#include "StorageBase.h"


class StorageFactory {
public:
    static StorageFactory &getInstance();

    static StorageFactory *createStorage(std::string type);


private:
    StorageFactory();

    ~StorageFactory();

    StorageFactory(const StorageFactory &);

    const StorageFactory &operator=(const StorageFactory &);
};


#endif //ROCKARBON_STORAGEFACTORY_H
