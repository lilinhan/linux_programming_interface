/*************************************************************************
    > File Name: t_fork.cpp
    > Author: lewin
    > Mail: lilinhan1303@gmail.com
    > Company:  Xiyou Linux Group
    > Created Time: Thu 15 Oct 2015 17:51:42 CST
 ************************************************************************/

#include<iostream>
#include<string>
#include<cstdlib>
#include<cerrno>
#include<unistd.h>
#include<sys/types.h>


static int idata = 111;

int main( int argc , char * argv[] )  {
    int istack = 222;
    pid_t childPid;

    switch(childPid = fork())  {
        case -1:perror("fork error");break;
        case 0:idata *= 3;
               istack *= 3;
               sleep(4);
               break;
        default:sleep(3);
                break;
    }

    printf("PID = %ld %s idata = %d istack = %d\n",(long)getpid(),(childPid == 0) ? "(child)" : "(parent)",idata, istack);
    return EXIT_SUCCESS;
}

