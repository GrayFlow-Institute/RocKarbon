//
// Created by yanyuhl on 18-3-18.
//

#ifndef ROCKARBON_LOGGER_H
#define ROCKARBON_LOGGER_H


#include <string>

class LoggerBase {
public:
    LoggerBase() = default;

    virtual ~LoggerBase() = default;

    // APIs
    virtual void init(std::string)=0;

    virtual void info(const std::string &)=0;

    virtual void debug(const std::string &)=0;

    virtual void warning(const std::string &)=0;

    virtual void error(const std::string &)=0;


};


#endif //ROCKARBON_LOGGER_H
