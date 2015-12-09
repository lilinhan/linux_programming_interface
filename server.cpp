/*************************************************************************
    > File Name: test1.cpp
    > Author: lewin
    > Mail: lilinhan1303@gmail.com
    > Organization: Xiyou Linux Group
    > Created Time: 2015年12月08日 星期二 21时14分38秒
 ************************************************************************/
#include<iostream>
#include<netinet/in.h>
#include<assert.h>
#include<unistd.h>
#include<cstring>
#include<cstdlib>
#include<errno.h>
#include<fcntl.h>

#include<sys/types.h>
#include<sys/socket.h>

#include<event.h>
#include<event2/bufferevent.h>

#include"server.h"

Socket::Socket() {
    listen_addr.sin_family = AF_INET;
    listen_addr.sin_addr.s_addr = INADDR_ANY;
    listen_addr.sin_port = htons(PORT);
}

Socket::~Socket(){}

void Socket::set_socket_option() {
    bool reuse = true;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (const char *)&reuse, sizeof(bool));
}

void Socket::socket_bind() {
    bind(listenfd, (struct sockaddr*)&listen_addr, sizeof(listen_addr));
}

void Socket::socket_listen() {
    listen(listenfd, 1024);
}

void Socket::set_listensocket_nonblocking() {
    int flags = fcntl(listenfd, F_GETFL);
    flags |= O_NONBLOCK;
    fcntl(listenfd, F_SETFL, flags);
}

void Socket::finished_init() {
    set_socket_option();
    socket_bind();
    socket_listen();
    set_listensocket_nonblocking();
}

void Socket::read_data_from_buffer(struct bufferevent *bev, void *arg){
#define MAX_LINE 1024
    char line[MAX_LINE+1];
    int n;
    int clientfd = bufferevent_getfd(bev);   //get client fd
    n = bufferevent_read(bev, line, MAX_LINE);
    while(n > 0) {
        line[n] = '\0';
        std::cout << "client:" << line << std::endl;
        bufferevent_write(bev, line, n);
    }
}

void Socket::write_data_to_buffer(struct bufferevent *bev, void *arg) {


}

void Socket::error_for_clientfd(struct bufferevent *bev, short event,void *arg) {
    int clientfd = bufferevent_getfd(bev);
    if(event & BEV_EVENT_TIMEOUT)  {
        std::cout << "Time out" << std::endl;
    }else if(event & BEV_EVENT_EOF) {
        std::cout << "Connection closed" << std::endl;
    }else if(event & BEV_EVENT_ERROR)  {
        std::cout << "Some other error" << std::endl;
    }
    bufferevent_free(bev);
}

void Socket::handle_accept(short event, void *arg) {  //accept client connect and add the client fd in bufferevent
    int client_fd;
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);

    client_fd = accept(client_fd, (struct sockaddr *)&client_addr, &client_len);
    if(client_fd < 0) {
        printf("accept error\n");
        exit(1);
    }

    struct event_base *base_ev = (struct event_base *)arg;

    struct bufferevent *bev = bufferevent_socket_new(base_ev, client_fd, BEV_OPT_CLOSE_ON_FREE);
    bufferevent_setcb(bev, read_data_from_buffer, NULL, error_for_clientfd, base_ev);
    bufferevent_enable(bev, EV_READ | EV_WRITE | EV_PERSIST);
    bufferevent_setwatermark(bev, EV_READ, 0, 1024);
}

int main(int argc, char *argv[])
{
    Socket listen_socket;
    struct current_base = event_init(); //initialize a global variable
    struct event ev;

    event_set(&ev, listen_socket.listenfd, EV_READ | EV_PERSIST, listen_socket.handle_accept, (void *)&ev);
    event_base_set(&current_base, &ev);

    event_base_loop(current_base, 0);
    return EXIT_SUCCESS;
}

