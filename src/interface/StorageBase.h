//
// Created by yanyuhl on 18-3-15.
//

#ifndef ROCKARBON_STORAGEBASE_H
#define ROCKARBON_STORAGEBASE_H

#include <string>

class StorageBase {
public:

    StorageBase() = default;

    virtual ~StorageBase() = default;

    // 对于一种存储的某个路径等，应该只有一个实例(避免了文件加锁的繁琐)，所以禁止复制
    StorageBase(const StorageBase &) = delete;

    const StorageBase &operator=(const StorageBase &)= delete;

    // APIs

    virtual bool init(std::string)=0;

    virtual std::string get(long long key)=0;

    virtual bool deal(long long key, std::string value)=0;

    virtual std::string deal(std::string data)=0;

    virtual bool match(long long key)=0;

    virtual bool sync()=0;
};


#endif //ROCKARBON_STORAGEBASE_H
