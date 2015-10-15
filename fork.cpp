/*************************************************************************
    > File Name: fork.cpp
    > Author: lewin
    > Mail: lilinhan1303@gmail.com
    > Company:  Xiyou Linux Group
    > Created Time: Thu 15 Oct 2015 17:42:46 CST
 ************************************************************************/

#include<iostream>
#include<string>
#include<cstdlib>
#include<cerrno>
#include<unistd.h>
#include<error.h>

int main( int argc , char * argv[] )  {
    pid_t childPid;
    switch(childPid = fork())  {
        case -1:perror("fork error!");break;
        case 0:std::cout << "this is child process , id = !"<< getpid() << std::endl;break;
        default: std::cout << "this is parent process!" <<getpid() << std::endl;sleep(2);break;
    }
    std::cout << "main function" << std::endl;

    return EXIT_SUCCESS;
}

