//
// Created by yanyuhl on 18-3-14.
//

#include <mutex>
#include <unordered_map>
#include "Env.h"
#include "../log/LoggerFactory.h"
#include "../storage/StorageFactory.h"

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


string Env::getData(StringEnv type) {

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

LoggerBase *Env::getLogger(string info) {
    int type = getData(NumberEnv::LOGGER);

    if ((int) LoggerType::RELEASE == type) {
        return LoggerFactory::getInstance().createStorage(LoggerType::RELEASE, info);
    } else if ((int) LoggerType::DEBUG == type) {
        return LoggerFactory::getInstance().createStorage(LoggerType::DEBUG, info);
    } else {
        return nullptr;
    }

}

StorageBase *Env::getStorage(string data) {
    int type = getData(NumberEnv::STORAGE);

    if ((int) StorageType::FILE == type) {
        return StorageFactory::getInstance().createStorage(StorageType::FILE, data);
    } else {
        return nullptr;
    }
}
