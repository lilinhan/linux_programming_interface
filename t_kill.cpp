/*************************************************************************
    > File Name: t_kill.cpp
    > Author: lewin
    > Mail: lilinhan1303@gmail.com
    > Company:  Xiyou Linux Group
    > Created Time: 2015年09月03日 星期四 16时35分10秒
 ************************************************************************/

#include<iostream>
#include<string>
#include<cstdlib>
#include<cerrno>
#include<signal.h>
#include<unistd.h>


int main( int argc , char * argv[] )  {
    int s , pid;
    if(argc != 2)  {
        std::cout << "error!" << std::endl;
        exit(EXIT_SUCCESS);
    }

    pid = std::atoi(argv[1]);
    s = kill(pid , SIGTERM);
    if( s == -1 )  {
        std::cout << "kill error" << std::endl;
    }

    return EXIT_SUCCESS;
}

