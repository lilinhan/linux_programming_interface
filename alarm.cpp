/*************************************************************************
    > File Name: alarm_setitimer.cpp
    > Author: lewin
    > Mail: lilinhan1303@gmail.com
    > Company:  Xiyou Linux Group
    > Created Time: Tue 13 Oct 2015 14:22:05 CST
 ************************************************************************/

#include<iostream>
#include<string>
#include<cstdlib>
#include<cerrno>
#include<unistd.h>
#include<signal.h>


void signal_fn(int sig)
{
    std::cout << "alarm!" << std::endl;
    alarm(5);
    std::cout << "wait 5 seconds!" << std::endl;
    return;
}

int main( int argc , char * argv[] )  {
    signal(SIGALRM , signal_fn);
    alarm(3);
    std::cout << "In main function!  And wait 3 seconds!" << std::endl;
    while(1)  {
        pause();
    }
    return EXIT_SUCCESS;
}

