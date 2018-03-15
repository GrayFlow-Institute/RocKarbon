//
// Created by yanyuhl on 18-3-15.
//

#ifndef ROCKARBON_RSAGUARD_H
#define ROCKARBON_RSAGUARD_H

#include <string>

class RSAGuard {
public:

    RSAGuard();

    ~RSAGuard();

    RSAGuard(const RSAGuard &other);

    RSAGuard &operator=(const RSAGuard &other);



    //APIs
    // TODO 添加实现

    int makeKeys();

    bool isInited();

    void init(std::string prvKey, std::string pubKey);

    int encode(std::string otherPubKey, std::string data);

    int decode(std::string data);

    const std::string getPrivateKey();

    const std::string getPublicKey();

private:
    class Impl; // 为了封装实现 :)
    Impl *mImpl;
};

#endif //ROCKARBON_RSAGUARD_H
