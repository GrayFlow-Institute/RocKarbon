//
// Created by yanyuhl on 18-3-15.
//

#ifndef ROCKARBON_STORAGEBASE_H
#define ROCKARBON_STORAGEBASE_H

#include <string>

class StorageBase {
    StorageBase() = default;

    virtual ~StorageBase() = default;

    virtual void init(std::string data)=0;

    virtual std::string get(long long key)=0;

    virtual std::string deal(long long key, std::string value)=0;

    virtual int match(long long key, const std::string &value)=0;

    virtual void sync()=0;
};


#endif //ROCKARBON_STORAGEBASE_H
