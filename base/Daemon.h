//
// Created by yanyuhl on 18-3-14.
//

#ifndef ROCKARBON_DAEMON_H
#define ROCKARBON_DAEMON_H


class Daemon {
public:
    int becomeDaemon(bool isChroot, bool isIORedirection);
};


#endif //ROCKARBON_DAEMON_H
