/*************************************************************************
    > File Name: direct_read.cpp
    > Author: lewin
    > Mail: lilinhan1303@gmail.com
    > Company:  Xiyou Linux Group
    > Created Time: Thu 08 Oct 2015 11:01:12 CST
 ************************************************************************/

#include<iostream>
#include<string>
#include<cstdlib>
#include<cerrno>
#include<fcntl.h>
#include<malloc.h>
#include<string.h>
#include<unistd.h>

#define BUF_SIZE 1024

int main( int argc , char * argv[] )
{
    int fd ;
    int ret;
    unsigned char * buf;

    ret = posix_memalign((void **)&buf , 512 , BUF_SIZE);
    if(ret) {
        perror("posix_memalign failed!");
        exit(1);
    }

    memset(buf , 'c' , BUF_SIZE);

    fd = open("./1.text" , O_WRONLY | O_CREAT | O_DIRECT , 0755);
    if(fd < 0)  {
        perror("open ./1.text failed");
        exit(1);
    }

    ret = write(fd , buf , BUF_SIZE);
    if( ret < 0 )  {
        perror("write ./1.text failed!");
        exit(1);
    }

    free(buf);
    close(fd);
    return EXIT_SUCCESS;
}

