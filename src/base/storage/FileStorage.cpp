//
// Created by yanyuhl on 18-3-21.
//

#include "FileStorage.h"

class FileStorage::Impl {
public:
    // TODO 实现

};

// TOOD 实现

FileStorage::FileStorage() : mImpl(new FileStorage::Impl()) {}

FileStorage::~FileStorage() { delete (mImpl); }

bool FileStorage::init(std::string data) {
    return false;
}

std::string FileStorage::get(long long key) {
    return "";
}

std::string FileStorage::deal(long long key, std::string value) {
    return "";
}

int FileStorage::match(long long key, const std::string &value) {
    return 0;
}

bool FileStorage::sync() {

}
