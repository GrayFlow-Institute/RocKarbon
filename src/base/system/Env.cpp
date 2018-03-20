//
// Created by yanyuhl on 18-3-14.
//

#include "Env.h"
#include <mutex>
#include <unordered_map>

using namespace std;

class Env::Impl {
public:
    unordered_map<char, string> stringDatas;
    unordered_map<char, int> numberDatas;

};

static mutex m;

Env &Env::getInstance() {
    lock_guard<std::mutex> locker(m);
    static Env env;
    return env;
}

Env::Env() : mImpl(new Env::Impl()) {};

Env::~Env() { delete (mImpl); }


bool Env::putData(StringEnv type, string data) {

    auto tmp = (mImpl->stringDatas).find((char) type);

    if (tmp == mImpl->stringDatas.end()) {
        (mImpl->stringDatas).insert({(char) type, move(data)});
    } else {
        return false;
    }

    return true;
}

bool Env::putData(NumberEnv type, int data) {
    auto tmp = (mImpl->numberDatas).find((char) type);

    if (tmp == mImpl->numberDatas.end()) {
        (mImpl->numberDatas).insert({(char) type, data});
    } else {
        return false;
    }

    return true;
}


const string &Env::getData(StringEnv type) {

    auto tmp = (mImpl->stringDatas).find((char) type);

    if (tmp == mImpl->stringDatas.end()) {
        return "";
    } else {
        return tmp->second;
    }
}

int Env::getData(NumberEnv type) {
    auto tmp = (mImpl->numberDatas).find((char) type);

    if (tmp == mImpl->numberDatas.end()) {
        return -1;
    } else {
        return tmp->second;
    }
}
