/*************************************************************************
    > File Name: LibeventServer.cpp
    > Author: lewin
    > Mail: lilinhan1303@gmail.com
    > Company:  Xiyou Linux Group
    > Created Time: Fri 06 Nov 2015 09:31:40 CST
 ************************************************************************/

#include<iostream>
#include<string>
#include<cstdlib>
#include<cerrno>
#include<event.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<fcntl.h>
#include<sys/socket.h>

struct event_base *main_base;
static const char MESSAGE[] = "Hello,World!\n";

void accept_handle(const int sfd, const short event, void *arg)  {
    std::cout << "accept handle" << std::endl;
    struct sockaddr_in addr;
    socklen_t addrlen = sizeof(addr);
    int fd = accept(sfd, (struct sockaddr *)&addr, &addrlen);
    struct bufferevent* buf_ev;
    buf_ev = bufferevent_new(fd , NULL, NULL, NULL, NULL);

    buf_ev->wm_read.high = 4096;
    std::cout << "event write" << std::endl;
    bufferevent_write(buf_ev, MESSAGE, strlen(MESSAGE));
}

int main( int argc , char * argv[] )  {
    std::cout << "hello man!" << std::endl;
    main_base = event_init();
    if(main_base) {
        std::cout << "init event OK!" << std::endl;
    }

    int sListen;
    sListen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof(struct sockaddr_in));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    int portnumber = 8080;
    server_addr.sin_port = htons(portnumber);




    return EXIT_SUCCESS;
}

