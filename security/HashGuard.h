//
// Created by yanyuhl on 18-3-15.
//

#ifndef ROCKARBON_HASHGUARD_H
#define ROCKARBON_HASHGUARD_H


class HashGuard {
public:
    static HashGuard &getInstance();

private:
    HashGuard();

    ~HashGuard();

    HashGuard(const HashGuard &);

    const HashGuard &operator=(const HashGuard &);

    class Impl; // 为了封装实现 :)

    Impl *mImpl;
};


#endif //ROCKARBON_HASHGUARD_H
