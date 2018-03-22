//
// Created by yanyuhl on 18-3-22.
//

#ifndef ROCKARBON_PROTOCOL_H
#define ROCKARBON_PROTOCOL_H

namespace rockarbon::protocol {
    // 协议字符串
    const std::string PROT_HEAD = "rockarbon/1.0\n";
    const std::string PROT_HEARBEAT_REQ = PROT_HEAD + "hearbeat request\n";
    const std::string PROT_HEARBEAT_RES = PROT_HEAD + "hearbeat response\n";
    const std::string PROT_SYNC_FIRST = PROT_HEAD + "sync first\n";
    const std::string PROT_SYNC_MORE = PROT_HEAD + "sync more\n";
    const std::string PROT_SYNC_DONE = PROT_HEAD + "sync done\n";
}

#endif //ROCKARBON_PROTOCOL_H
