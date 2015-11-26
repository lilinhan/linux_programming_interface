/*************************************************************************
	> File Name: libeventtest4.cpp
	> Author: lewin
	> Mail: lilinhan1303@gmail.com
	> Company: Xiyou Linux Group
	> Created Time: 2015年11月26日 星期四 15时14分18秒
 ************************************************************************/

#include<iostream>
#include<event.h>

struct event ev;
struct timeval tv;

void time_cb(int fd, short event, void *argc) {
    std::cout << "Timer wakeup!\n";
    event_add(&ev, &tv);
}

int main(int argc, char* argv[])
{
    struct event_base *base = event_init();

    tv.tv_sec = 10;
    tv.tv_usec = 0;
    evtimer_set(&ev, time_cb, NULL);
    event_add(&ev, &tv);
    event_base_dispatch(base);
    return EXIT_SUCCESS;
}

