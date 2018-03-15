//
// Created by yanyuhl on 18-3-15.
//

#ifndef ROCKARBON_RSAGUARD_H
#define ROCKARBON_RSAGUARD_H

#include <string>

class RSAGuard {
public:
    void init(std::string prvKey, std::string pubKey);

    int encode(std::string otherPubKey, std::string data);

    int decode(std::string data);


private:
    class Impl; // 为了封装实现 :)
    Impl *mImpl;
};

#endif //ROCKARBON_RSAGUARD_H
