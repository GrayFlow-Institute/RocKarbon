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

    // TODO

    bool init(std::string data) override;

    std::string get(long long key) override;

    std::string deal(long long key, std::string value) override;

    int match(long long key, const std::string &value) override;

    void sync() override;
};


#endif //ROCKARBON_FILESTORAGE_H
