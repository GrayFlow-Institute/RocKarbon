//
// Created by yanyuhl on 18-3-14.
//

#ifndef ROCKARBON_ENV_H
#define ROCKARBON_ENV_H

#include <string>

enum class EnvData : char {


};

class Env {
public:
    static Env &getInstance();
    // TODO 添加实现

    std::string getInstanceOnlyCode(EnvData type);


private:
    Env();

    ~Env();

    Env(const Env &);

    const Env &operator=(const Env &);

    class Impl; // 为了封装实现 :)

    Impl *mImpl;
};


#endif //ROCKARBON_ENV_H
