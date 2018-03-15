//
// Created by yanyuhl on 18-3-14.
//

#ifndef ROCKARBON_DAEMON_H
#define ROCKARBON_DAEMON_H


class Daemon {
public:
    Daemon();

    ~Daemon();

    int becomeDaemon();

    int debugDaemon();

private:
    class Impl;

    Impl *mImpl;

    // 禁止复制
    Daemon(const Daemon &);

    const Daemon &operator=(const Daemon &);
};


#endif //ROCKARBON_DAEMON_H
