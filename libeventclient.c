/*************************************************************************
    > File Name: libeventclient.c
    > Author: lewin
    > Mail: lilinhan1303@gmail.com
    > Company:  Xiyou Linux Group
    > Created Time: Mon 09 Nov 2015 22:03:31 CST
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
#include<pthread.h>
#include<sys/socket.h>


int main(int argc , char * argv[])  {
    int client_fd;
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(8001);

    client_fd = socket(PF_INET, SOCK_STREAM, 0);
    if(client_fd < 1)  {
        puts("client socket error");
        return 0;
    }

    int ret = connect(client_fd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
    if(ret < 0)  {
        puts("client connect error");
        return 0;
    }

    char buf[1024];
    int len = recv(client_fd, buf, 1024, 0);
    buf[len] = '\0';
    puts(buf);

    char * x = "Hello World, sdfsdf4fhwjkerhfkhef";
    send(client_fd, x, strlen(x), 0);

    memset(buf, 0, 1024);
    int len2 = recv(client_fd, buf, 1024, 0);
    buf[len2] = '\0';
    puts(buf);

    shutdown(client_fd, 2);
    return EXIT_SUCCESS;
}

