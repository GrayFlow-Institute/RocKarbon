//
// Created by yanyuhl on 18-3-15.
//

#include <mutex>
#include <cstring>
#include <string>

#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1

#include <cryptopp/md5.h>
#include <cryptopp/sha.h>

#include "HashGuard.h"


using namespace CryptoPP;
using namespace std;

class HashGuard::Impl {
public:

};

static std::mutex m;

HashGuard &HashGuard::getInstance() {
    std::lock_guard<std::mutex> locker(m);
    static HashGuard hash;
    return hash;
}

const std::string HashGuard::getMD5(const std::string &data) {

    byte digest[Weak::MD5::DIGESTSIZE];

    Weak::MD5 hash;
    hash.CalculateDigest(digest, (const byte *) data.c_str(), data.length());

    string out;
    char tmp[3];
    for (auto i : digest) {
        sprintf(tmp, "%02x", i);
        out += tmp;
    }
    return out;
}

const std::string HashGuard::getSHA256(const std::string &data) {
    byte digest[SHA256::DIGESTSIZE];

    SHA256().CalculateDigest(digest, (const byte *) data.c_str(), data.length());

    string out;
    char tmp[3];
    for (auto i : digest) {
        sprintf(tmp, "%02x", i);
        out += tmp;
    }
    return out;
}

HashGuard::HashGuard() = default;

HashGuard::~HashGuard() = default;