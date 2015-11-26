/*************************************************************************
    > File Name: t_uname.c
    > Author: lewin
    > Mail: lilinhan1303@gmail.com
    > Company:  Xiyou Linux Group
    > Created Time: Sun 04 Oct 2015 11:04:54 CST
 ************************************************************************/

#include<sys/types.h>
#include<sys/stat.h>
#include<limits.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<signal.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<sys/utsname.h>



int main(int argc , char * argv[])  {
    struct utsname uts;
    if(uname(&uts) == -1)  {
        printf("uname");
        exit(0);
    }

    printf("Node name : %s\n" , uts.nodename);
    printf("System name : %s\n" , uts.sysname);
    printf("Releae  : %s \n" , uts.release);
    printf("Version : %s \n" , uts.version);
    printf("Machine : %s\n" , uts.machine);

#ifdef _GNU_SOURCE
    printf("Domain name : %s \n" , uts.domainname);
#endif
    return EXIT_SUCCESS;
}

