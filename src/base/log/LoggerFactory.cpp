//
// Created by yanyuhl on 18-3-18.
//

#include <mutex>
#include "LoggerFactory.h"
#include "DebugLogger.h"
#include "ReleaseLogger.h"

static std::mutex m;

LoggerFactory &LoggerFactory::getInstance() {
    std::lock_guard<std::mutex> locker(m);
    static LoggerFactory factory;
    return factory;
}

LoggerFactory::LoggerFactory() = default;

LoggerFactory::~LoggerFactory() = default;

LoggerBase *LoggerFactory::createStorage(LoggerType type, std::string info) {
    LoggerBase *logger = nullptr;
    if (type == LoggerType::DEBUG) {
        logger = new DebugLogger();
        logger->init(info);
    } else if (type == LoggerType::RELEASE) {
        logger = new ReleaseLogger();
        // 没用就不初始化了
    }
    return logger;
}

