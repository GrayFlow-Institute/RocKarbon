//
// Created by yanyuhl on 18-3-21.
//


#include <gtest/gtest.h>
#include <fstream>
#include "../../src/field/system/Env.h"
#include "../../src/interface/StorageBase.h"

using namespace std;

TEST(Storage, FileStorage) {
    string TEST_PATH = "./test.dat";
    string ERROR_PATH1 = "/test.dat";
    string ERROR_PATH2 = "/";
    string WRITE_DATA = "4 abcd4\n3 abcd3\n2 abcd2\n1 abcd1";

    fstream f;
    f.open(TEST_PATH, ios::trunc | ios::out);
    f.write(WRITE_DATA.c_str(), WRITE_DATA.size());
    f.close();

    Env &env = Env::getInstance();
    StorageBase *storage;

    // 空环境
    EXPECT_EQ(env.getStorage(), nullptr);


    // 无类型
    env.putData(StringEnv::STORAGE_PATH, TEST_PATH);
    EXPECT_EQ(env.getStorage(), nullptr);
    env.clear();

    // 无权限路径
    env.putData(NumberEnv::STORAGE, (int) StorageType::FILE);
    env.putData(StringEnv::STORAGE_PATH, ERROR_PATH1);
    EXPECT_EQ(env.getStorage(), nullptr);
    env.clear();

    // 错误路径
    env.putData(NumberEnv::STORAGE, (int) StorageType::FILE);
    env.putData(StringEnv::STORAGE_PATH, ERROR_PATH2);
    EXPECT_EQ(env.getStorage(), nullptr);
    env.clear();

    // 正确获取
    env.putData(NumberEnv::STORAGE, (int) StorageType::FILE);
    EXPECT_EQ(env.getStorage(), nullptr);
    env.putData(StringEnv::STORAGE_PATH, TEST_PATH);


    storage = env.getStorage();
    EXPECT_NE(storage, nullptr);

    EXPECT_EQ(storage->get(1), "abcd1");
    EXPECT_EQ(storage->get(123), "");

    EXPECT_EQ(storage->match(100), false);
    EXPECT_EQ(storage->match(1), true);

    EXPECT_EQ(storage->sync(), true);

    EXPECT_EQ(storage->deal("6 d\n5 r\n"), "more");
    EXPECT_EQ(storage->deal("7 e\n" + WRITE_DATA), "6 d\n5 r\n");
    EXPECT_EQ(storage->deal(WRITE_DATA), "7 e\n6 d\n5 r\n");

    EXPECT_EQ(storage->sync(), true);

    storage = env.getStorage(); // 重新初始化，检查 sync 是否真的写入磁盘

    EXPECT_EQ(storage->get(7), "e");
    EXPECT_EQ(storage->get(6), "d");

}
