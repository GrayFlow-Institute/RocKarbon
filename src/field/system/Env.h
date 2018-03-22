//
// Created by yanyuhl on 18-3-14.
//

#ifndef ROCKARBON_ENV_H
#define ROCKARBON_ENV_H

#include <string>

#include "../../interface/LoggerBase.h"
#include "../../interface/LoggerType.h"

#include "../../interface/StorageBase.h"
#include "../../interface/StorageType.h"


enum class StringEnv : char {
    INSTANCE_ONLY_CODE = 0,
    IP,
    SERVER_NAME,
    SERVER_INFO,
    PASSWORD,
    STORAGE_PATH,
};

enum class NumberEnv : char {
    PORT,
    LOGGER,
    STORAGE,


};

class Env {
public:
    static Env &getInstance();

    std::string getData(StringEnv type);

    int getData(NumberEnv type);

    bool putData(StringEnv type, std::string data);

    bool putData(NumberEnv type, int data);

    void clear();

    LoggerBase *getLogger(std::string info);

    StorageBase *getStorage();

private:
    Env();

    ~Env();

    Env(const Env &);

    const Env &operator=(const Env &);

    class Impl; // 为了封装实现 :)

    Impl *mImpl;
};


#endif //ROCKARBON_ENV_H
