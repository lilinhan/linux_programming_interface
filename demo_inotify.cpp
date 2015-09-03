/*************************************************************************
    > File Name: demo_inotify.cpp
    > Author: lewin
    > Mail: lilinhan1303@gmail.com
    > Company:  Xiyou Linux Group
    > Created Time: 2015年09月02日 星期三 20时24分37秒
 ************************************************************************/

#include<iostream>
#include<string>
#include<cstdlib>
#include<cerrno>
#include<sys/inotify.h>
#include<limits.h>
#include<unistd.h>

#define BUF_LEN 10*(sizeof(struct inotify_event))

int main( int argc , char * argv[] )  {
    int inotifyfd;
    ssize_t numRead;
    char buf[BUF_LEN];
    struct inotify_event *event;
    char * p;
    std::string path = "/home/lewin/linux_programming_interface/hello.txt";

    inotifyfd = inotify_init();
    if(inotifyfd == -1)  {
        std::cout << "create inotifyfd is error!"<< std:: endl;
        exit(-1);
    }

    if(( -1 == inotify_add_watch(inotifyfd , path.c_str() , IN_ALL_EVENTS)))   {
        std::cout << "add watch error!" << std::endl;
        exit(0);
    }


    while(1) {
        numRead = read(inotifyfd , buf , BUF_LEN);
        if(numRead == 0){
            std::cout << "read from inotifyfd return 0!" << std::endl;
        }
        if( -1 == numRead )  {
            std::cout << "read error!" << std::endl;
            exit(0);
        }

        event = (struct inotify_event *)buf;
        if( event->mask & IN_OPEN )  {
            std::cout << "IN_OPEN" <<std::endl;
        }
        if( event->mask & IN_MODIFY )  {
            std::cout << "IN_MODIFY" <<std::endl;
        }
    }
    return EXIT_SUCCESS;
}

