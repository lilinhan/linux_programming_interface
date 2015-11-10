/*************************************************************************
    > File Name: libeventserver.c
    > Author: lewin
    > Mail: lilinhan1303@gmail.com
    > Company:  Xiyou Linux Group
    > Created Time: Mon 09 Nov 2015 21:06:07 CST
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
#include<fcntl.h>

#include<event2/event.h>
#include<event2/bufferevent.h>

void read_cb(struct bufferevent *bev, void *arg) {
#define MAX_LINE 256
    char line[MAX_LINE+1];
    int n;
    evutil_socket_t fd = bufferevent_getfd(bev);
    n = bufferevent_read(bev, line, MAX_LINE);
    while(n > 0) {
        line[n] = '\0';
        printf("fd = %u, read line:%s\n", fd, line);
        bufferevent_write(bev, line, n);
    }
    printf("haha\n");
}

void write_cb(struct bufferevent *bev, void *arg) {}
void error_cb(struct bufferevent *bev, short event, void *arg) {
    evutil_socket_t fd = bufferevent_getfd(bev);
    printf("fd = %u, ", fd);
    if(event & BEV_EVENT_TIMEOUT)  {
        printf("TIMED OUT\n");
    }else if(event & BEV_EVENT_EOF) {
        printf("connection closed\n");
    }else if(event & BEV_EVENT_ERROR) {
        printf("some other error\n");
    }
    bufferevent_free(bev);
}

void do_accept(evutil_socket_t fd ,short event, void * arg) {
    int client_socketfd;
    struct sockaddr_in client_addr;
    int in_size = sizeof(struct sockaddr_in);

    client_socketfd = accept(fd, (struct sockaddr *)&client_addr, &in_size);
    if(client_socketfd < 0) {
        printf("accept error\n");
        exit(1);
    }

    struct event_base *base_ev = (struct event_base *)arg;

    char *msg = "Welcome to My socket";
    int size = send(client_socketfd, msg, strlen(msg), 0);

    //struct event * ev;
    //ev = event_new(base_ev, client_socketfd, BEV_EVENT_TIMEOUT | BEV_READ | EV_PERSIST, do_read, base_ev);
    //event_add(ev,NULL);

    struct bufferevent *bev = bufferevent_socket_new(base_ev, client_socketfd, BEV_OPT_CLOSE_ON_FREE);
    bufferevent_setcb(bev, read_cb, NULL, error_cb, base_ev);
    bufferevent_enable(bev, EV_READ|EV_WRITE|EV_PERSIST);
    bufferevent_setwatermark(bev, EV_READ, 0, 10);
}

int main(int argc , char * argv[])  {
    int server_socketfd;
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8001);

    server_socketfd = socket(PF_INET, SOCK_STREAM, 0);
    if(server_socketfd < 0) {
        puts("socket error");
        return 0;
    }

    evutil_make_listen_socket_reuseable(server_socketfd);
    evutil_make_socket_nonblocking(server_socketfd);

    if(bind(server_socketfd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) < 0) {
        puts("bind error");
        return 0;
    }

    listen(server_socketfd, 5);

    struct event_base *base_ev;
    base_ev = event_base_new();
    const char *x = event_base_get_method(base_ev);
    printf("METHOD:%s\n", x);

    struct event *ev;
    ev = event_new(base_ev, server_socketfd, EV_TIMEOUT | EV_READ | EV_PERSIST, do_accept, base_ev);

    event_add(ev, NULL);
    event_base_dispatch(base_ev);

    event_base_free(base_ev);
    return EXIT_SUCCESS;
}

