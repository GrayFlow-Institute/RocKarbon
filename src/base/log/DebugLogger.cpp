//
// Created by yanyuhl on 18-3-18.
//

#include "DebugLogger.h"
#include <mutex>
#include <string>

class DebugLogger::Impl {
public:
    std::string info;
};

DebugLogger::DebugLogger() : mImpl(new DebugLogger::Impl()) {}

DebugLogger::~DebugLogger() {
    delete mImpl;
}

void DebugLogger::init(std::string info) {
    mImpl->info = info;
}

void DebugLogger::info(std::string outs) {

}

void DebugLogger::debug(std::string outs) {

}

void DebugLogger::warning(std::string outs) {

}

void DebugLogger::error(std::string outs) {

}
