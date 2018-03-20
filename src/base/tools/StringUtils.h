//
// Created by yanyuhl on 18-3-20.
//

#ifndef ROCKARBON_STRINGUTILS_H
#define ROCKARBON_STRINGUTILS_H

#include <string>

class StringUtils {
public:
    StringUtils() { srand(time(NULL)); }

    std::string getRandomString(int len);

    std::string getRandomString(const std::string &domain, int len);
};


#endif //ROCKARBON_STRINGUTILS_H
