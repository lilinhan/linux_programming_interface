/*************************************************************************
    > File Name: time.cpp
    > Author: lewin
    > Mail: lilinhan1303@gmail.com
    > Company:  Xiyou Linux Group
    > Created Time: 2015年08月31日 星期一 20时41分42秒
 ************************************************************************/

#include<iostream>
#include<string>
#include<cstdlib>
#include<cerrno>
#include<sys/time.h>

int main( int argc , char * argv[] )  {
    struct timeval tv;
    struct timezone tz;
    gettimeofday(&tv,&tz);

    std::cout << "tv_sec:" << tv.tv_sec << std::endl;   //秒数
    std::cout << "tv_usec:" << tv.tv_usec << std::endl; //微秒数
    std::cout << "tz_minuteswest:" << tz.tz_minuteswest << std::endl;  //和Greewich时间差了多少分钟
    std::cout << "tz_dsttime:" << tz.tz_dsttime << std::endl;  //日光节约时间的状态

    return EXIT_SUCCESS;
}

