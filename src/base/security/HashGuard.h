//
// Created by yanyuhl on 18-3-15.
//

#ifndef ROCKARBON_HASHGUARD_H
#define ROCKARBON_HASHGUARD_H

#include <string>

class HashGuard {
public:
    static HashGuard &getInstance();

    // TODO 添加实现

    const std::string getMD5(const std::string &data);

    const std::string getSHA256(const std::string &data);

private:
    HashGuard();

    ~HashGuard();

    HashGuard(const HashGuard &);

    const HashGuard &operator=(const HashGuard &);

    class Impl; // 为了封装实现 :)

    Impl *mImpl;
};


#endif //ROCKARBON_HASHGUARD_H
