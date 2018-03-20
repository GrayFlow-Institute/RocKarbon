//
// Created by yanyuhl on 18-3-19.
//


#include <gtest/gtest.h>
#include <string>
#include "../../src/base/security/HashGuard.h"

using namespace std;

TEST(Security, MD5) {
    string md5sum = "e19d5cd5af0378da05f63f891c7467af";
    HashGuard &h = HashGuard::getInstance();
    EXPECT_EQ(h.getMD5("abcd1234"), md5sum);
}


TEST(Security, SHA256) {
    string sha256sum = "e9cee71ab932fde863338d08be4de9dfe39ea049bdafb342ce659ec5450b69ae";
    HashGuard &h = HashGuard::getInstance();
    EXPECT_EQ(h.getSHA256("abcd1234"), sha256sum);}


TEST(BasicTest, EQTest) {
    EXPECT_EQ(6, 6);
}


