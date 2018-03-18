//
// Created by yanyuhl on 18-3-18.
//

#ifndef ROCKARBON_LOGGER_H
#define ROCKARBON_LOGGER_H


#include <string>

class Logger {
public:
    Logger() = default;

    virtual ~Logger() = default;

    // APIs
    virtual void init(std::string)=0;

    virtual void info(std::string)=0;

    virtual void debug(std::string)=0;

    virtual void warning(std::string)=0;

    virtual void error(std::string)=0;


};


#endif //ROCKARBON_LOGGER_H
