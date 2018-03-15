//
// Created by yanyuhl on 18-3-14.
//

#ifndef ROCKARBON_DAEMON_H
#define ROCKARBON_DAEMON_H


class Daemon {
public:
    int becomeDaemon();
    int debugDaemon();

private:
    class Impl;
    Impl* mImpl;
};


#endif //ROCKARBON_DAEMON_H
