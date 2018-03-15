//
// Created by yanyuhl on 18-3-15.
//

#ifndef ROCKARBON_STORAGEBASE_H
#define ROCKARBON_STORAGEBASE_H

#include <string>

class StorageBase {
    StorageBase() = default;

    ~StorageBase() = default;

    virtual void init(std::string data)=0;

    virtual std::string get(const std::string &key)=0;

    virtual std::string deal(std::string key, std::string value)=0;

    virtual int match(const std::string &key, const std::string &value)=0;

    virtual void sync()=0;
};


#endif //ROCKARBON_STORAGEBASE_H
