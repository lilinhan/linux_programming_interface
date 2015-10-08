/*************************************************************************
    > File Name: procfs_pidmax.c
    > Author: lewin
    > Mail: lilinhan1303@gmail.com
    > Company:  Xiyou Linux Group
    > Created Time: Sun 04 Oct 2015 10:40:35 CST
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

#define MAX_LINE 100

int main(int argc , char * argv[])  {
    int fd;
    char line[MAX_LINE];
    ssize_t n;

    fd = open("/proc/sys/kernel/pid_max , (argc > 1) ? O_RDWR : O_RDONLY");

    if(fd == -1 )  {
        printf("open error\n");
        exit(0);
    }

    n = read(fd , line , MAX_LINE);
    if ( n == -1)  {
        printf("read error\n");
        exit(0);
    }

    if(argc > 1)  {
        printf("%.*s" , (int) n , line);
        exit(0);
    }

    if(argc > 1) {
        if(write(fd , argv[1] , strlen(argv[1])) != strlen(argv[1]))  {
                printf("write error!\n");
                exit(0);
        }

        system("echo /proc/sys/kernel/pid_max now contains "
                "'cat /proc/sys/kernel/pid_max'");
    }

    return EXIT_SUCCESS;
}

