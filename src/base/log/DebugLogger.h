//
// Created by yanyuhl on 18-3-18.
//

#ifndef ROCKARBON_DEBUGLOGGER_H
#define ROCKARBON_DEBUGLOGGER_H

#include "../../interface/LoggerBase.h"

class DebugLogger : public LoggerBase {
public:
    DebugLogger();

    ~DebugLogger() override;

    // APIs
    void init(std::string info) override;

    void info(const std::string&outs) override;

    void debug(const std::string& outs) override;

    void warning(const std::string& outs) override;

    void error(const std::string& outs) override;

private:
    class Impl;

    Impl *mImpl;

    // 因为保存着特定类的信息，所以禁止拷贝

    DebugLogger(const DebugLogger &);

    const DebugLogger &operator=(const DebugLogger &);


};


#endif //ROCKARBON_DEBUGLOGGER_H
