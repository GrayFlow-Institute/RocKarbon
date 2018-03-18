//
// Created by yanyuhl on 18-3-18.
//

#include "DebugLogger.h"

#include <ctime>
#include <mutex>
#include <iostream>

constexpr int BUFF_SIZE = 2048;

using namespace std;

class DebugLogger::Impl {
public:
    string info;

    void printLog(const string &, const string &);

private:

    string getFormatTime();
};

string DebugLogger::Impl::getFormatTime() {
    time_t rawTime;
    struct tm *timeInfo;
    char buffer[BUFF_SIZE];

    time(&rawTime);
    timeInfo = localtime(&rawTime);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeInfo);

    return string(buffer);
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

void DebugLogger::info(const std::string &outs) {
    mImpl->printLog("Info", outs);
}

void DebugLogger::debug(const std::string &outs) {
    mImpl->printLog("Debug", outs);

}

void DebugLogger::warning(const std::string &outs) {
    mImpl->printLog("Warning", outs);

}

void DebugLogger::error(const std::string &outs) {
    mImpl->printLog("Error", outs);

}
