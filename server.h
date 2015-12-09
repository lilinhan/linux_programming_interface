/*************************************************************************
    > File Name: test1.cpp
    > Author: lewin
    > Mail: lilinhan1303@gmail.com
    > Organization: Xiyou Linux Group
    > Created Time: 2015年12月08日 星期二 21时14分38秒
 ************************************************************************/
#pragma once

#include<iostream>
#include<netinet/in.h>
#include<sys/socket.h>
#include<assert.h>
#include<unistd.h>
#include<cstring>
#include<cstdlib>
#include<errno.h>
#include<fcntl.h>

#include<event.h>
#include<event2/bufferevent.h>

#define SERVERIP "127.0.0.1"
#define PORT 9999

class Socket{
    private:
        struct sockaddr_in listen_addr; //server ip
        //int port;  //server ip
        int listenfd;   //server listen socket

    public:
        Socket();
        ~Socket();

        void set_socket_option();  //set socket option(like reuse)
        void socket_bind();  //bind the socket
        void socket_listen();  //listen the socket
        void set_listensocket_nonblocking();  //set nonblocking

        void finished_init();  //finished all configure

        void handle_accept(short event, void *arg);  //handle the client connect

        void read_data_from_buffer(struct bufferevent *bev, void *arg); //callback function for read data
        void write_data_to_buffer(struct bufferevent *bev, void *arg); //callback function for write data
        void error_for_clientfd(struct bufferevent *bev, short event, void *arg);  //callback function for error
};



