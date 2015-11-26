/*************************************************************************
    > File Name: abort.c
    > Author: lewin
    > Mail: lilinhan1303@gmail.com
    > Company:  Xiyou Linux Group
    > Created Time: Sun 11 Oct 2015 14:28:14 CST
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

#define USE_SIG_LONG_JMP

static sigjmp_buf senv;

void handler(int sig)
{
    printf("In the handler!\n");
#ifdef USE_SIG_LONG_JMP
    siglongjmp(senv , 1);
    printf("Never see it!\n");
#endif
}

void m_abort(void)
{
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set , SIGABRT);
    sigprocmask(SIG_UNBLOCK , &set , NULL);
    printf("m_abort : raise first SIGABRT.\n");

    raise(SIGABRT);
    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESETHAND;
    sa.sa_handler = SIG_DFL;
    sigaction(SIGABRT , &sa , NULL);
    printf("m_abort : raise second SIGABRT.\n");
    raise(SIGABRT);
}

int main(int argc , char * argv[])  {
    printf("Now call the abort.\n");
    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = handler;
    sigaction(SIGABRT , &sa , NULL);
#ifdef USE_SIG_LONG_JMP
    if(sigsetjmp(senv , 1) == 0)  {
        m_abort();
    }else {
        printf("abort failed.  1\n");
    }
#else
    m_abort();
    printf("abort failed.  2\n");
#endif
    return EXIT_SUCCESS;
}

