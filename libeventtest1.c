/*************************************************************************
    > File Name: libeventtest1.c
    > Author: lewin
    > Mail: lilinhan1303@gmail.com
    > Company:  Xiyou Linux Group
    > Created Time: Sun 08 Nov 2015 22:48:03 CST
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

#include<event2/event.h>
#include<event2/bufferevent.h>

int main(int argc , char * argv[])  {
    printf("Init a event_base!\n");
    struct event_base * base;
    base = event_base_new();
    const char *x = event_base_get_method(base);

    printf("Method:%s\n", x);

    int y = event_base_dispatch(base);

    event_base_free(base);

    return EXIT_SUCCESS;
}

