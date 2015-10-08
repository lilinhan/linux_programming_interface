/*************************************************************************
    > File Name: TestServerPressure.cpp
    > Author: lewin
    > Mail: lilinhan1303@gmail.com
    > Company:  Xiyou Linux Group
    > Created Time: 2015年09月24日 星期四 10时39分15秒
 ************************************************************************/

#include<iostream>
#include<string>
#include<cstdlib>
#include<cerrno>
#include<assert.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/epoll.h>
#include<fcntl.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#define MAXNUM 10000

class TestServerPressure {
    private:
        std::string targetip;
        int targetport;
        int socketfds[MAXNUM];
        struct sockaddr_in address;

    public:
        TestServerPressure(std::string ip , int port):targetip(ip) , targetport(port) {
            bzero( & address , sizeof(address));
            address.sin_family = AF_INET;
            inet_pton( AF_INET , targetip.c_str() , &address.sin_addr);
            address.sin_port = htons( port );
            for( int i = 0 ; i < MAXNUM ; ++i )  {
                socketfds[i] = socket(PF_INET , SOCK_STREAM , 0);
                std::cout << socketfds[i] << std::endl;
                if( socketfds[i] < 0)  {
                    usleep(50000);
                }
            }
        }
        ~TestServerPressure() {}

        void setip(std::string ip) {
            this->targetip = ip;
        }
        void setport(int port)  {
            this->targetport = port;
        }

        int setNonBlocking( int fd )  {
            int old_option = fcntl( fd , F_GETFL);
            int new_option = old_option | O_NONBLOCK;
            fcntl( fd , F_SETFL , new_option);
            return old_option;
        }

        void start_conn(int num)  {
            for( int i = 0 ; i < num ; ++i )  {
                if(connect( socketfds[i] , (struct sockaddr*)&address , sizeof(address)) < 0)  {
                    std::cout << "NO." << i << "  connection faild!" << std::endl;
                   // std::cout << "socket ID:"  <<  socketfds[i] << "lalalala" << std::endl;
                }
                std::cout << "connected " << i << "client!" << std::endl;
                usleep(500);
            }
        }

        void close_conn ()  {
            for(int i = 0 ; i < MAXNUM ; ++i)  {
                close(socketfds[i]);
            }
        }
};

int main( int argc , char * argv[] )  {
    assert(argc == 4);
    TestServerPressure a(argv[1] , atoi(argv[2]));
    a.start_conn(atoi(argv[3]));
    return EXIT_SUCCESS;
}

