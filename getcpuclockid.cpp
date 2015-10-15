/*************************************************************************
    > File Name: getcpuclockid.cpp
    > Author: lewin
    > Mail: lilinhan1303@gmail.com
    > Company:  Xiyou Linux Group
    > Created Time: Wed 14 Oct 2015 10:54:38 CST
 ************************************************************************/

#include<iostream>
#include<string>
#include<cstdlib>
#include<cerrno>
#include<time.h>
#include<stdlib.h>
#include<assert.h>

int main( int argc , char * argv[] )  {
    if( 0 == clock_getcpuclockid(0 , CLOCK_REALTIME))  {

    }
    return EXIT_SUCCESS;
}

