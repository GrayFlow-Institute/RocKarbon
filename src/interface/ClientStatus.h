//
// Created by yanyuhl on 18-3-16.
//

#ifndef ROCKARBON_SERVICESTATUS_H
#define ROCKARBON_SERVICESTATUS_H

enum class Status : char {
    NOTINIT,
    CLOSED,
    SYNCED,
    SYNCING
};

#endif //ROCKARBON_SERVICESTATUS_H
