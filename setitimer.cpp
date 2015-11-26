/*************************************************************************
    > File Name: setitimer.cpp
    > Author: lewin
    > Mail: lilinhan1303@gmail.com
    > Company:  Xiyou Linux Group
    > Created Time: Tue 13 Oct 2015 14:46:30 CST
 ************************************************************************/

#include<iostream>
#include<string>
#include<cstdlib>
#include<cerrno>
#include<sys/time.h>
#include<signal.h>
#include<unistd.h>
#include<sys/types.h>

int sec;
void sigroutine( int signo )
{
    switch(signo)  {
        case SIGALRM: std::cout << "Catch a signal -- SIGALRM" << std::endl;
                      signal(SIGALRM , sigroutine);
                      break;
        case SIGVTALRM: std::cout << "Catch a signal -- SIGVYALRM" << std::endl;
                        signal(SIGVTALRM , sigroutine);
                        break;
    }
    return;
}

int main( int argc , char * argv[] )  {
    struct itimerval value , ovalue , value2;
    sec = 5;
    std::cout << "process id is " << getpid() << std::endl;
    signal(SIGALRM , sigroutine);
    signal(SIGVTALRM , sigroutine);
    value.it_value.tv_sec = 1;
    value.it_value.tv_usec = 0;
    value.it_interval.tv_sec = 1;
    value.it_interval.tv_usec = 0;

    setitimer(ITIMER_REAL , &value , &ovalue);

    value2.it_value.tv_sec = 0;
    value2.it_value.tv_usec = 500000;
    value2.it_interval.tv_sec = 0;
    value2.it_interval.tv_usec = 500000;

    setitimer(ITIMER_VIRTUAL , &value2 , &ovalue);

    for(;;)  {

    }
    return EXIT_SUCCESS;
}

