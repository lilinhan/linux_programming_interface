/*************************************************************************
    > File Name: test.cpp
    > Author: lewin
    > Mail: lilinhan1303@gmail.com
    > Organization: Xiyou Linux Group
    > Created Time: 2015年12月07日 星期一 16时35分56秒
 ************************************************************************/
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<sys/types.h>
#include<sys/socket.h>
#include<fcntl.h>

#include<event.h>
#include<event2/bufferevent.h>

void accept_handle(const int sfd, const short event, void *arg)
{
    struct sockaddr_in addr;
    socklen_t addrlen = sizeof(addr);

    int fd = accept(sfd, (struct sockaddr*)&addr, &addrlen);

    buf_ev = bufferevent_new(fd, bufferevent_on_read, NULL, NULL, fd);
    buf_ev->wm_read.high = 4096;
    bufferevent_base_set(main_base, buf_ev);
    bufferevent_enable(buf_ev, EV_READ);
}

int main(int argc, char *argv[])
{
    auto main_base = event_init();

    struct sockaddr_in listen_addr;
    int port = 9999;
    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);

    memset(&listen_addr, 0, sizeof(listen_addr));

    listen_addr.sin_family = AF_INET;
    listen_addr.sin_addr.s_addr = INADDR_ANY;
    listen_addr.sin_port = htons(port);

    int nRecvBuf = 32*1024;
    setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, (const char*)&nRecvBuf, sizeof(nRecvBuf));

    bind(listen_fd, (struct sockaddr *)&listen_addr, sizeof(listen_addr));
    listen(listen_fd, 1024);

    int flags = fcntl(listen_fd, F_GETFL);
    flags |= O_NONBLOCK;
    fcntl(listen_fd, F_SETFL, flags);


    struct event ev;
    event_set(&ev, listen_fd, EV_READ | EV_PERSIST, accept_handle, (void *)&ev);

    event_add(&ev, NULL);

    event_base_loop(main_base, 0);
    return EXIT_SUCCESS;
}

