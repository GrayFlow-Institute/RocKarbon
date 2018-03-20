//
// Created by yanyuhl on 18-3-20.
//

#include "StringUtils.h"
#include <random>
#include <ctime>

using namespace std;

std::string StringUtils::getRandomString(int len) {
    if (len <= 0) {
        return "";
    }
    string domain = "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpeQqRrSsTtUuVvWwXxYyZz0123456789";
    return getRandomString(domain, len);
}

std::string StringUtils::getRandomString(const string &domain, int len) {
    if (domain.length() <= 0 || len <= 0) return "";

    auto domain_len = domain.length();

    string sum = "";

    for (int i = 0; i < len; ++i) {
        auto x = rand() % domain_len;
        sum += domain.c_str()[x];
    }

    return sum;
}
