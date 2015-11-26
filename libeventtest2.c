/*************************************************************************
	> File Name: libeventtest2.c
	> Author: lewin
	> Mail: lilinhan1303@gmail.com
	> Company: Xiyou Linux Group
	> Created Time: 2015年11月24日 星期二 22时05分04秒
 ************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>

#include<libevent/event/event.h>
#include<libevent/event/bufferevent.h>
#include<libevent/event/event_struct.h>

struct event *ev;
struct timeval tv;

void time_cb(int fd, short event, void *argc) {
    printf("timer wakeup\n");
    event_add(&ev, &tv);
}

int main(int argc, char *argv[])
{
    struct event_base *base = event_init();

    tv.tv_sec = 10;
    tv.tv_usec = 0;
    evtimer_set(ev, time_cb, NULL);
    event_add(ev, &tv);
    event_base_dispatch(base);
    return EXIT_SUCCESS;
}


