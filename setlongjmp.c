/*************************************************************************
    > File Name: setlongjmp.c
    > Author: lewin
    > Mail: lilinhan1303@gmail.com
    > Company:  Xiyou Linux Group
    > Created Time: Sun 11 Oct 2015 15:51:15 CST
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
#include<setjmp.h>
#include<sys/time.h>

sigjmp_buf jmp_env;

static void connect_alarm()
{
    siglongjmp(jmp_env , 1);
    printf("lalalal\n");
}

int main(int argc , char * argv[])  {
    int sec_timeout = 3;
    int run_time = 4;

    printf("timeout = %d , run time = %d\n", sec_timeout , run_time);
    if(sec_timeout) {
        signal(SIGALRM , connect_alarm);
        alarm(sec_timeout);
        printf("set timeout.\n");
        if(sigsetjmp(jmp_env , 1))  {
            printf("timeout \n");
            goto out;
        }
    }

    sleep(run_time);
    printf("running ...\n");

out:
    if(sec_timeout)  {
        alarm(0);
        printf("cancel timeout\n");
    }

    return EXIT_SUCCESS;
}

