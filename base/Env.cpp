//
// Created by yanyuhl on 18-3-14.
//

#include "Env.h"
#include <mutex>

class Env::Impl{
public:
};

static std::mutex m;

Env &Env::getInstance() {
    std::lock_guard<std::mutex> locker(m);
    static Env env;
    return env;
}

Env::Env() = default;

Env::~Env() = default;

