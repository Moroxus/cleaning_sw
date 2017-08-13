//
// Created by lukas on 1/13/17.
//

#ifndef CLEANING_SW_ENVIRONMENT_H
#define CLEANING_SW_ENVIRONMENT_H

#include <string>
#include <stdlib.h>
#include <pwd.h>
#include <unistd.h>


class Environment {
public:
    static std::string getUserName()
    {
        using namespace std;
        struct passwd *pw;
        uid_t uid;
        string userName;

        uid = geteuid();
        pw = getpwuid(uid);
        if (pw) userName = pw->pw_name;
        return userName;
    }
};


#endif //CLEANING_SW_ENVIRONMENT_H
