//
// Created by yanyuhl on 18-3-21.
//

#ifndef ROCKARBON_FILESTORAGE_H
#define ROCKARBON_FILESTORAGE_H

#include <string>
#include "../../interface/StorageBase.h"

class FileStorage : public StorageBase {

public:
    static FileStorage &getInstance();

    // APIs
    bool init(std::string path) override;

    std::string get(long long key) override;

    bool deal(long long key, std::string value) override;

    std::string deal(std::string data) override;

    bool match(long long key) override;

    bool sync() override;

private:
    FileStorage();

    ~FileStorage() override;

    class Impl; // 为了封装实现 :)
    Impl *mImpl;
};


#endif //ROCKARBON_FILESTORAGE_H
