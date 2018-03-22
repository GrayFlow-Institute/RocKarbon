//
// Created by yanyuhl on 18-3-21.
//

#include "FileStorage.h"
#include <unordered_map>
#include <vector>
#include <list>
#include <string>
#include <mutex>
#include <fstream>
#include <sstream>
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
    // 三清操作
    mImpl->aid.clear();
    mImpl->historyData.clear();
    mImpl->path.clear();

    fstream f;
    f.open(path, ios::in|ios::out);
    if (!f) {
        return false;
    }
    stringstream sbuffer;
    sbuffer << f.rdbuf();
    f.close();
    string buff(sbuffer.str());
    if (deal(buff) == "error") {
        return false;
    }
    mImpl->path = path;
    return true;
}

string FileStorage::get(long long key) {
    if (mImpl->path.empty()) { return ""; }

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
 * 如果出现错误，则返回 "error"
 * 如果都不存在——即客户端发送的数据不足，则返回 "more"
 * 如果部分存在——即客户端发送的数据足够，则返回本地多出的数据(客户端未同步的数据)
 *
 * */

string FileStorage::deal(string data) {
    if (data.empty()) {
        string buff;
        for (auto key:mImpl->aid) {
            buff = to_string(key) + " " + mImpl->historyData[key] + "\n" + buff;
        }
        return buff;
    }

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
                while (true) {
                    c = data.c_str()[i++];
                    if (c != '\n' && c != '\0') {
                        buff += c;
                    } else {
                        break;
                    }
                }
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
    long long lastSameKey = -1;
    bool dealStatu = true;
    bool preDealStatu = true;

    for (int i = keys.size() - 1; i >= 0; --i) {
        auto key = keys[i];
        auto value = values[i];

        preDealStatu = dealStatu;
        dealStatu = deal(key, value);
        if ((!preDealStatu && dealStatu && lastSameKey == -1) || // 服务器部分领先
            (!preDealStatu && !dealStatu && i == 0)) { // 服务器完美领先
            if (i != keys.size() - 1) {
                lastSameKey = keys[i + 1];
            }
            // 如果数据足够，并且有多，则返回服务器多出来的数据
            for (auto it = mImpl->aid.begin(); it != mImpl->aid.end(); ++it) {
                if (*it > lastSameKey) {
                    for (; it != mImpl->aid.end(); ++it) {
                        if (*it == key)continue;
                        buff = to_string(*it) + " " + mImpl->historyData[*it] + "\n" + buff;
                    }
                    break;
                }
            }
        }

    }
    // 一直插入成功，即数据不够，所以请求新的数据——客户端完美领先
    if (buff.empty()) {
        return "more";
    }

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
    if (mImpl->path.empty()) { return false; }
    return !(mImpl->historyData.end() == (mImpl->historyData).find(key));
}

bool FileStorage::sync() {
    if (mImpl->path.empty()) { return false; }
    string buff;
    try {
        for (auto key:mImpl->aid) {
            buff = to_string(key) + " " + mImpl->historyData[key] + "\n" + buff;
        }

        fstream f;
        f.open(mImpl->path, ios::trunc | ios::out);
        f << buff;
        f.close();
    } catch (exception &e) {
        return false;
    }
    return true;


}

