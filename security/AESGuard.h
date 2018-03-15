//
// Created by yanyuhl on 18-3-15.
//

#ifndef ROCKARBON_GUARDS_H
#define ROCKARBON_GUARDS_H

#include <string>

class AESGuard {
public:
    void init(std::string passwd);

    int encode(std::string data);

    int decode(std::string data);

private:
    class Impl; // 为了封装实现 :)
    Impl *mImpl;
};


#endif //ROCKARBON_GUARDS_H
