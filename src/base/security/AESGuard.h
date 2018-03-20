//
// Created by yanyuhl on 18-3-15.
//

#ifndef ROCKARBON_GUARDS_H
#define ROCKARBON_GUARDS_H

#include <string>

class AESGuard {
public:
    AESGuard();

    ~AESGuard();

    AESGuard(const AESGuard &other);

    AESGuard &operator=(const AESGuard &other);

    // APIs

    bool isInited();

    bool init(std::string passwd);

    bool encode(std::string &data);

    bool decode(std::string &data);

    const std::string getPassword();

private:
    class Impl; // 为了封装实现 :)
    Impl *mImpl;
};


#endif //ROCKARBON_GUARDS_H
