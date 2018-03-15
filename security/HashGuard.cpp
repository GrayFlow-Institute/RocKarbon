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

HashGuard::HashGuard() = default;

HashGuard::~HashGuard() = default;