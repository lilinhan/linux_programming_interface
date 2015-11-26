/*************************************************************************
    > File Name: gettime.cpp
    > Author: lewin
    > Mail: lilinhan1303@gmail.com
    > Company:  Xiyou Linux Group
    > Created Time: Wed 14 Oct 2015 10:41:31 CST
 ************************************************************************/

#include<iostream>
#include<string>
#include<cstdlib>
#include<cerrno>
#include<time.h>

timespec diff(timespec start , timespec end)
{
    timespec temp;
    if((end.tv_nsec - start.tv_nsec) < 0 )  {
        temp.tv_sec = end.tv_sec - start.tv_sec - 1;
        temp.tv_nsec = 1000000000 + end.tv_nsec - start.tv_nsec;
    }
    return temp;
}

int main( int argc , char * argv[] )  {
    timespec time1 , time2;
    int temp;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID , & time1);
    for( int i = 0 ; i < 242000000 ; i++ )  {
        temp += temp;
    }
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID , &time2);
    std::cout << diff(time1 , time2).tv_sec << ":" << diff(time1 , time2).tv_nsec << std::endl;
    return EXIT_SUCCESS;
}

