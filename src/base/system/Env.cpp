//
// Created by yanyuhl on 18-3-14.
//

#include "Env.h"
#include <mutex>
#include <unordered_map>
#include <memory>

using namespace std;

class Env::Impl {
public:
    unordered_map<char, shared_ptr<string *> > stringDatas;
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


bool Env::putData(StringEnv type, string *data) {

//    auto tmp = (mImpl->stringDatas).find((char) type);
//
//    if (tmp == mImpl->stringDatas.end()) {
//        (mImpl->stringDatas).insert((char) type, data);
//    } else {
//        return true;
//    }
//
//    return true;
}

bool Env::putData(NumberEnv type, int data) {

}


string *Env::getData(StringEnv type) {

}

int Env::getData(NumberEnv type) {
    return 0;
}
