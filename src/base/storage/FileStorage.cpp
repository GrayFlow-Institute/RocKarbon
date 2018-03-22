//
// Created by yanyuhl on 18-3-21.
//

#include "FileStorage.h"
#include <unordered_map>
#include <vector>
#include <list>
#include <string>
#include <mutex>
#include <cstring>

using namespace std;

class FileStorage::Impl {
public:
    unordered_map<long long, string> historyData;
    list<long long> aid;
    string path;
};

static mutex m;

FileStorage &FileStorage::getInstance() {
    lock_guard<mutex> locker(m);
    static FileStorage storage;
    return storage;
}


FileStorage::FileStorage() : mImpl(new FileStorage::Impl()) {}

FileStorage::~FileStorage() { delete (mImpl); }

bool FileStorage::init(string path) {




    mImpl->path = path;
    return true;
}

string FileStorage::get(long long key) {
    auto tmp = (mImpl->historyData).find(key);
    if (tmp == mImpl->historyData.end()) {
        return "";
    } else {
        return tmp->second;
    }
}

/* *
 *
 * 按照行添加，从大到小，数据格式例如：
 * 3 stringData
 * 2 stringData
 * 1 stringData
 *
 * 如果都不存在——即客户端发送的数据不足，则返回 "more"
 * 如果部分存在——即客户端发送的数据足够，则返回本地多出的数据(客户端未同步的数据)
 * 如果恰好同步——即客户端和服务端此时数据相同，则返回 "" 空文本
 * 如果出现错误，则返回 "error"
 *
 * */

string FileStorage::deal(string data) {
    lock_guard<mutex> locker(m);

    vector<long long> keys;
    vector<string> values;

    try {
        string buff;
        int i = 0;
        while (true) {
            char c = data.c_str()[i++];
            if (strchr("1234567890", c) != nullptr) {
                buff += c;
            } else if (strchr(" ", c) != nullptr) {
                keys.push_back(stoll(buff));
                buff.clear();
                do {
                    c = data.c_str()[++i];
                    buff += c;
                } while (c != '\n' && c != '\0');
                values.push_back(buff);
                buff.clear();
            }
            if (c == '\0') { break; }
        }

        if (keys.size() != values.size()) {
            return "error";
        }
    } catch (exception &e) {
        return "error";
    }

    string buff;
    long long lastKey = 0;

    for (int i = keys.size() - 1; i < 0; --i) {
        auto key = keys[i];
        auto value = values[i];

        bool dealStatu = deal(key, value);
        if (!dealStatu) { lastKey = key; }
        if (dealStatu && buff.empty()) {
            for (auto it = mImpl->aid.begin(); it != mImpl->aid.end(); ++it) {
                long long aidKey = *it;
                if (aidKey > lastKey) {
                    for (; it != mImpl->aid.end(); ++it) {
                        buff += to_string(*it) + " " + mImpl->historyData[*it] + "\n";
                    }
                    break;
                }
            }
        }
    }

    // 一直插入成功，即数据不够，所以请求新的数据
    if (buff.empty()) {
        return "more";
    }

    // 如果数据足够，并且有多，则返回服务器多出来的数据
    return buff;
}


/* *
 *
 * false 即存在，插入失败
 * true  即不存在，插入成功
 *
 * */
bool FileStorage::deal(long long key, string value) {
    if (match(key)) {
        return false;
    }

    mImpl->historyData.insert({key, value});

    bool isInsert = false;
    for (auto item = mImpl->aid.begin(); item != mImpl->aid.end(); ++item) {
        if (key < *item) {
            isInsert = true;
            mImpl->aid.insert(item, key);
            break;
        }
    }
    if (!isInsert) {
        mImpl->aid.push_back(key);
    }
    return true;
}

bool FileStorage::match(long long key) {
    return !(mImpl->historyData.end() == (mImpl->historyData).find(key));
}

bool FileStorage::sync() {
// TODO
}

