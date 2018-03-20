//
// Created by yanyuhl on 18-3-15.
//

#include "AESGuard.h"

#include <iostream>
#include <cstring>
#include <aes.h>
#include <modes.h>
#include <filters.h>

using namespace std;
using namespace CryptoPP;

class AESGuard::Impl {
public:
    bool inited = false;
    string passwd;

};

AESGuard::AESGuard() : mImpl(new AESGuard::Impl()) {}

AESGuard::~AESGuard() { delete (mImpl); }

AESGuard::AESGuard(const AESGuard &other) : mImpl(new AESGuard::Impl(*(other.mImpl))) {}

AESGuard &AESGuard::operator=(const AESGuard &other) {
    if (&other == this) {
        return *this;
    }

    delete (mImpl);
    mImpl = nullptr;

    mImpl = new AESGuard::Impl(*other.mImpl);

    return *this;
}

bool AESGuard::isInited() {
    return mImpl->inited;
}

bool AESGuard::init(string passwd) {
    if (passwd.size() > AES::DEFAULT_KEYLENGTH) {
        return false;
    }
    mImpl->passwd = move(passwd);
    mImpl->inited = true;
    return true;
}

const string AESGuard::getPassword() {
    return mImpl->passwd;
}

bool AESGuard::encode(string &data) {
    if (!isInited())
        return false;

    byte key[AES::DEFAULT_KEYLENGTH], iv[AES::BLOCKSIZE];
    memset(key, 0x00, AES::DEFAULT_KEYLENGTH);
    memset(iv, 0x00, AES::BLOCKSIZE);
    strcpy(reinterpret_cast<char *>(key), mImpl->passwd.c_str());

    AES::Encryption aesEncryption(key, AES::DEFAULT_KEYLENGTH);
    CBC_Mode_ExternalCipher::Encryption cbcEncryption(aesEncryption, iv);

    std::string ciphertext;
    StreamTransformationFilter stfEncryptor(cbcEncryption, new StringSink(ciphertext));
    stfEncryptor.Put(reinterpret_cast<const unsigned char *>( data.c_str()), data.size());
    stfEncryptor.MessageEnd();

    data = ciphertext;

    return true;
}

bool AESGuard::decode(string &data) {
    if (!isInited())
        return false;

    byte key[AES::DEFAULT_KEYLENGTH], iv[AES::BLOCKSIZE];
    memset(key, 0x00, AES::DEFAULT_KEYLENGTH);
    memset(iv, 0x00, AES::BLOCKSIZE);
    strcpy(reinterpret_cast<char *>(key), mImpl->passwd.c_str());

    string decryptedtext;

    AES::Decryption aesDecryption(key, AES::DEFAULT_KEYLENGTH);
    CBC_Mode_ExternalCipher::Decryption cbcDecryption(aesDecryption, iv);

    StreamTransformationFilter stfDecryptor(cbcDecryption, new StringSink(decryptedtext));
    stfDecryptor.Put(reinterpret_cast<const unsigned char *>( data.c_str()), data.size());
    stfDecryptor.MessageEnd();

    data = decryptedtext;

    return true;
}





