//
// Created by yanyuhl on 18-3-18.
//

#ifndef ROCKARBON_RELEASELOGGER_H
#define ROCKARBON_RELEASELOGGER_H

#include "../interface/LoggerBase.h"

class ReleaseLogger : public LoggerBase {
public:
    ReleaseLogger() = default;

    ~ReleaseLogger() override = default;;

    // APIs
    void init(std::string info) override {};

    void info(const std::string &outs) override {};

    void debug(const std::string &outs) override {};

    void warning(const std::string &outs) override {};

    void error(const std::string &outs) override {};

private:
    // 一个空的。。。干嘛要拷贝

    ReleaseLogger(const ReleaseLogger &);

    const ReleaseLogger &operator=(const ReleaseLogger &);


};


#endif //ROCKARBON_RELEASELOGGER_H
