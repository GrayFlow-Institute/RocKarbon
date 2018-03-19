//
// Created by yanyuhl on 18-3-15.
//

#include <mutex>
#include "HashGuard.h"

class HashGuard::Impl {
public:
};

static std::mutex m;

HashGuard &HashGuard::getInstance() {
    std::lock_guard<std::mutex> locker(m);
    static HashGuard hash;
    return hash;
}

const std::string HashGuard::getMD5(const std::string &data) {


    return "";
}

const std::string HashGuard::getSHA256(const std::string &data) {
    return "";
}

HashGuard::HashGuard() = default;

HashGuard::~HashGuard() = default;