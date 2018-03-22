//
// Created by yanyuhl on 18-3-21.
//

#include "FileStorage.h"
#include <unordered_map>
#include <string>
#include <mutex>

using namespace std;

class FileStorage::Impl {
public:
    unordered_map<long long, string> historyData;
};

static mutex m;

FileStorage &FileStorage::getInstance() {
    lock_guard<std::mutex> locker(m);
    static FileStorage storage;
    return storage;
}


// TOOD 实现

FileStorage::FileStorage() : mImpl(new FileStorage::Impl()) {}

FileStorage::~FileStorage() { delete (mImpl); }

bool FileStorage::init() {
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

