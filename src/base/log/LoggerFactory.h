//
// Created by yanyuhl on 18-3-18.
//

#ifndef ROCKARBON_LOGGERFACTORY_H
#define ROCKARBON_LOGGERFACTORY_H

#include <string>
#include "../../interface/LoggerType.h"
#include "../../interface/LoggerBase.h"

class LoggerFactory {
public:
    static LoggerFactory &getInstance();

    LoggerBase *createStorage(LoggerType type, std::string info);

private:
    LoggerFactory();

    ~LoggerFactory();

    LoggerFactory(const LoggerFactory &);

    const LoggerFactory &operator=(const LoggerFactory &);
};


#endif //ROCKARBON_LOGGERFACTORY_H
