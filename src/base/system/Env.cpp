//
// Created by yanyuhl on 18-3-14.
//

#include "Env.h"
#include <mutex>

class Env::Impl {
public:
    // TODO 添加实现

};

static std::mutex m;

Env &Env::getInstance() {
    std::lock_guard<std::mutex> locker(m);
    static Env env;
    return env;
}

Env::Env() : mImpl(new Env::Impl()) {};

Env::~Env() { delete (mImpl); }
