/*************************************************************************
    > File Name: t_sysconf.cpp
    > Author: lewin
    > Mail: lilinhan1303@gmail.com
    > Company:  Xiyou Linux Group
    > Created Time: 2015年08月31日 星期一 21时21分51秒
 ************************************************************************/

#include<iostream>
#include<string>
#include<cstdlib>
#include<cerrno>
#include<errno.h>
#include<unistd.h>
static void sysconfPrint(const char * msg , int name )  {
    long lim;
    errno = 0;
    lim = sysconf(name);
    if(lim != -1)  {
        std::cout << msg << "\t" << lim << std::endl;
    }else {
        if(errno == 0)  {
            std::cout << msg << "(indeterminate)" << std::endl;
        }else {
            exit(0);
        }
    }
}

int main( int argc , char * argv[] )  {
    sysconfPrint("_SC_ARG_MAX:   ",_SC_ARG_MAX);
    sysconfPrint("_SC_LOGIN_NAME_MAX:   ",_SC_LOGIN_NAME_MAX);
    sysconfPrint("_SC_OPEN_MAX:   ",_SC_OPEN_MAX);
    sysconfPrint("_SC_NGROUPS_MAX:   ",_SC_NGROUPS_MAX);
    sysconfPrint("_SC_PAGESIZE:   ",_SC_PAGESIZE);
    sysconfPrint("_SC_RTSIG_MAX:   ",_SC_RTSIG_MAX);

    return EXIT_SUCCESS;
}

