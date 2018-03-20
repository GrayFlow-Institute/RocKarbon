//
// Created by yanyuhl on 18-3-14.
//

#ifndef ROCKARBON_ENV_H
#define ROCKARBON_ENV_H

#include <string>
#include <memory>


enum class StringEnv : char {
    INSTANCE_ONLY_CODE = 0,
    IP,
    SERVER_NAME,
    SERVER_INFO,
};

enum class NumberEnv : char {
    PORT,


};

class Env {
public:
    static Env &getInstance();
    // TODO 添加实现

    std::string getData(StringEnv type);

    int getData(NumberEnv type);

    bool putData(StringEnv type, std::string data);

    bool putData(NumberEnv type, int data);


private:
    Env();

    ~Env();

    Env(const Env &);

    const Env &operator=(const Env &);

    class Impl; // 为了封装实现 :)

    Impl *mImpl;
};


#endif //ROCKARBON_ENV_H
