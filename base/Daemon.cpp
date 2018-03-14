//
// Created by yanyuhl on 18-3-14.
//

#include "Daemon.h"
#include <unistd.h>

/*
 * true = 1
 * false= 0
 * */
int Daemon::becomeDaemon(bool isChroot, bool isIORedirection) {
    int croot = 0;
    int ior = 0;
    if (!isChroot) {
        croot = 1;
    }
    if (!isIORedirection) {
        ior = 1;
    }
    return daemon(croot, ior);
}


