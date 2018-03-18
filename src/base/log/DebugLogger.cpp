//
// Created by yanyuhl on 18-3-18.
//

#include "DebugLogger.h"

#include <ctime>
#include <mutex>
#include <iostream>

using namespace std;

class DebugLogger::Impl {
public:
    string info;

    string getFormatTime();

    void printLog(const string &, const string &);
};

string DebugLogger::Impl::getFormatTime() {

}

void DebugLogger::Impl::printLog(const string &type, const string &log) {
    string outs = "[" + getFormatTime() + "] ";

    outs += "[" + type + "] ";
    outs += "[" + info + "] ";
    outs += log;

    cout << outs << endl;
}


DebugLogger::DebugLogger() : mImpl(new DebugLogger::Impl()) {}

DebugLogger::~DebugLogger() {
    delete mImpl;
}

void DebugLogger::init(std::string info) {
    mImpl->info = info;
}

void DebugLogger::info(const std::string& outs) {

}

void DebugLogger::debug(const std::string& outs) {

}

void DebugLogger::warning(const std::string& outs) {

}

void DebugLogger::error(const std::string& outs) {

}
