//
// Created by yanyuhl on 18-3-15.
//

#include "AESGuard.h"

class AESGuard::Impl {
public:
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





