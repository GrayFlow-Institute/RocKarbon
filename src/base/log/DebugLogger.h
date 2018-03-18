//
// Created by yanyuhl on 18-3-18.
//

#ifndef ROCKARBON_DEBUGLOGGER_H
#define ROCKARBON_DEBUGLOGGER_H

#include "../interface/Logger.h"

class DebugLogger : public Logger {
public:
    DebugLogger();

    ~DebugLogger() override;

    // APIs
    void init(std::string info) override;

    void info(std::string outs) override;

    void debug(std::string outs) override;

    void warning(std::string outs) override;

    void error(std::string outs) override;

private:
    class Impl;

    Impl *mImpl;

    // 因为保存着特定类的信息，所以禁止拷贝

    DebugLogger(const DebugLogger &);

    const DebugLogger &operator=(const DebugLogger &);


};


#endif //ROCKARBON_DEBUGLOGGER_H
