/*************************************************************************
    > File Name: libeventtest.c
    > Author: lewin
    > Mail: lilinhan1303@gmail.com
    > Company:  Xiyou Linux Group
    > Created Time: Mon 02 Nov 2015 23:01:35 CST
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

#define SERVER_PORT 8080
int debug = 0;

struct client{
    int fd;
    struct bufferevent *buf_ev;
};

int set_nonblock(int fd);
void buf_read_callback(struct bufferevent *incoming, void *arg);
void buf_write_callback(struct bufferevent *bev, void *arg);
void buf_error_callback(struct bufferevent *bev, short what, void *arg);
void accept_callback(int fd, short ev,void *arg);

int main(int argc , char * argv[])  {
    int socketlisten;
    struct sockaddr_in addresslisten;
    struct event accept_event;

    int reuse = 1;
    event_init();   //貌似是库里面自带的

    socketlisten = socket(AF_INET, SOCK_STREAM, 0);
    if(socketlisten < 0) {
        fprintf(stderr, "Failed to create listen socket");
        return 1;
    }

    memset(&addresslisten, 0, sizeof(addresslisten));

    addresslisten.sin_family = AF_INET;
    addresslisten.sin_addr.s_addr = INADDR_ANY; // INADDR_ANY??
    addresslisten.sin_port = htons(SERVER_PORT);

    if(bind(socketlisten, (struct sockaddr *)&addresslisten, sizeof(addresslisten)) < 0) {
        fprintf(stderr, "Failed to bind");
        return 1;
    }

    if(listen(socketlisten, 5) < 0) {
        fprintf(stderr, "Failed to listen");
        return 1;
    }

    setsockopt(socketlisten, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
    set_nonblock(socketlisten);

    event_set(&accept_event, socketlisten, EV_READ | EV_PERSIST, accept_callback, NULL);
    event_add(&accept_event, NULL);
    event_dispatch();
    close(socketlisten);


    return EXIT_SUCCESS;
}

