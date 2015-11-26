/*************************************************************************
    > File Name: clock_nanosleep.cpp
    > Author: lewin
    > Mail: lilinhan1303@gmail.com
    > Company:  Xiyou Linux Group
    > Created Time: Thu 15 Oct 2015 11:16:32 CST
 ************************************************************************/

#include<iostream>
#include<string>
#include<cstdlib>
#include<cerrno>
#include<time.h>
#include<sys/time.h>


int main( int argc , char * argv[] )  {
    struct timespec request;

    if(clock_gettime( CLOCK_REALTIME , &request ) == -1)  {
        std::cout << "error!" << std::endl;
        exit(0);
    }

    request.tv_sec += 5;
    int s = clock_nanosleep(CLOCK_REALTIME , TIMER_ABSTIME , &request , NULL);
    if(s != 0 )  {
        if( s == EINTR)  {
            std::cout << "Interrupted by signal hangdler!" << std::endl;
        }else {
            perror("clock_nanosleep");
        }
    }
    return EXIT_SUCCESS;
}

