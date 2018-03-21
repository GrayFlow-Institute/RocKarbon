//
// Created by yanyuhl on 18-3-21.
//

#ifndef ROCKARBON_FILESTORAGE_H
#define ROCKARBON_FILESTORAGE_H

#include <string>
#include "../../interface/StorageBase.h"

class FileStorage : public StorageBase {

public:
    FileStorage();

    ~FileStorage() override;

    // APIs
    bool init(std::string data) override;

    std::string get(long long key) override;

    std::string deal(long long key, std::string value) override;

    int match(long long key, const std::string &value) override;

    bool sync() override;

    // TODO 如何处理拷贝构造函数和赋值重载

private:
    class Impl; // 为了封装实现 :)
    Impl *mImpl;
};


#endif //ROCKARBON_FILESTORAGE_H
