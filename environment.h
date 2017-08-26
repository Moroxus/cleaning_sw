//
// Created by lukas on 1/13/17.
//

#ifndef CLEANING_SW_ENVIRONMENT_H
#define CLEANING_SW_ENVIRONMENT_H

#include <string>

#ifdef __linux
    #include <pwd.h>
    #include <unistd.h>
#elif _WIN32
    #include <windows.h>
    #include <Lmcons.h>
#endif

class Environment {
public:
    static std::string getUserName()
    {
        std::string userName;
        #ifdef __linux
            using namespace std;
            struct passwd *pw;
            uid_t uid;

            uid = geteuid();
            pw = getpwuid(uid);
            if (pw) userName = pw->pw_name;
        #elif _WIN32
            char username[UNLEN+1];
            DWORD username_len = UNLEN+1;
            GetUserName(username, &username_len);
            userName = username;
        #endif
        return userName;
    }
};


#endif //CLEANING_SW_ENVIRONMENT_H
