/*************************************************************************
    > File Name: dup.c
    > Author: lewin
    > Mail: lilinhan1303@gmail.com
    > Company:  Xiyou Linux Group
    > Created Time: Mon 02 Nov 2015 20:03:07 CST
 ************************************************************************/

#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

int main(int argc , char * argv[])  {
    char * buf = "hello world!";
    int fd = open("1.test" , O_CREAT | O_RDWR , 0766 );
    printf("Create a new file , FD = %d\n", fd);
    write(fd, (void *)buf, strlen(buf));
    close(fd);

    fd = open("1.test", O_APPEND | O_RDWR ,0766);
    int newfd = dup(fd);
    printf("After dup function. return value = %d\n", newfd);
    write(newfd, (void *)buf, strlen(buf));
    close(newfd);

    fd = open("1.test", O_APPEND | O_RDWR ,0766);
    int thirdfd = dup2(fd, 1000);
    printf("After dup2 function.The new FD = %d\n", thirdfd);
    write(1000, (void *)buf, strlen(buf));
    close(1000);
    return EXIT_SUCCESS;
}

