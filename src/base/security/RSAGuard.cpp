//
// Created by yanyuhl on 18-3-15.
//

#include "RSAGuard.h"

class RSAGuard::Impl {
public:
};

RSAGuard::RSAGuard() : mImpl(new RSAGuard::Impl()) {}

RSAGuard::~RSAGuard() { delete (mImpl); }

RSAGuard::RSAGuard(const RSAGuard &other) : mImpl(new RSAGuard::Impl(*(other.mImpl))) {}

RSAGuard &RSAGuard::operator=(const RSAGuard &other) {
    if (&other == this) {
        return *this;
    }

    delete (mImpl);
    mImpl = nullptr;

    mImpl = new RSAGuard::Impl(*other.mImpl);

    return *this;
}
