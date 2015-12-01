/*************************************************************************
	> File Name: sendotherdata.c
	> Author: lewin
	> Mail: lilinhan1303@gmail.com
	> Company: Xiyou Linux Group
	> Created Time: 2015年12月01日 星期二 22时18分27秒
 ************************************************************************/
#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<assert.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
    if(argc <= 2) {
        printf("usage:%s ip_address port_number\n",basename(argv[0]));
        return 1;
    }

    const char * ip = argv[1];
    int port = atoi(argv[2]);
    struct sockaddr_in server_address;
    bzero(&server_address, sizeof(server_address));
    server_address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &server_address.sin_addr);
    server_address.sin_port = htons(port);

    int socketfd = socket(PF_INET, SOCK_STREAM, 0);
    assert(socketfd >= 0);
    if(connect(socketfd, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        printf("connection failed!\n");
    }else {
        const char * oob_data = "abc";
        const char * normal_data = "123";
        send(socketfd, normal_data, strlen(normal_data), 0);
        send(socketfd, oob_data, strlen(oob_data), MSG_OOB);
        send(socketfd, normal_data, strlen(normal_data), 0);
    }
    close(socketfd);

    return EXIT_SUCCESS;
}


