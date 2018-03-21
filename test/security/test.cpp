//
// Created by yanyuhl on 18-3-19.
//


#include <gtest/gtest.h>
#include <string>
#include "../../src/base/security/HashGuard.h"
#include "../../src/base/security/AESGuard.h"

using namespace std;

TEST(Security, MD5) {
    string md5sum = "e19d5cd5af0378da05f63f891c7467af";
    HashGuard &h = HashGuard::getInstance();
    EXPECT_EQ(h.getMD5("abcd1234"), md5sum);
}


TEST(Security, SHA256) {
    string sha256sum = "e9cee71ab932fde863338d08be4de9dfe39ea049bdafb342ce659ec5450b69ae";
    HashGuard &h = HashGuard::getInstance();
    EXPECT_EQ(h.getSHA256("abcd1234"), sha256sum);
}


TEST(Security, AES) {
    string passwd = "abcd1234";
    string code = "mmmmmaaaaakkkkkilaksfdjlkashgkjasgaksdfasldk;gjasjdaaskl;fjasd;gjqwkabn \nasdflk";
    string tmp = code;

    AESGuard guard;
    // 未初始化功能测试
    EXPECT_EQ(guard.isInited(), false);
    EXPECT_EQ(guard.encode(code), false);
    EXPECT_EQ(guard.decode(code), false);

    // 空密码功能测试
    guard.init("");
    EXPECT_EQ(guard.isInited(), true);
    EXPECT_EQ(guard.getPassword(), "");

    EXPECT_EQ(guard.encode(code), true);
    EXPECT_EQ(code, tmp);

    EXPECT_EQ(guard.decode(code), true);
    EXPECT_EQ(code, tmp);



    // 正常功能测试
    guard.init(passwd);
    EXPECT_EQ(guard.isInited(), true);
    EXPECT_EQ(guard.getPassword(), passwd);

    EXPECT_EQ(guard.encode(code), true);
    EXPECT_NE(code, tmp);

    EXPECT_EQ(guard.decode(code), true);
    EXPECT_EQ(code, tmp);
}

