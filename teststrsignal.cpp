/*************************************************************************
    > File Name: teststrsignal.cpp
    > Author: lewin
    > Mail: lilinhan1303@gmail.com
    > Company:  Xiyou Linux Group
    > Created Time: 2015年09月03日 星期四 17时28分14秒
 ************************************************************************/

#include<iostream>
#include<string>
#include<cstdlib>
#include<cerrno>
#include<unistd.h>
#include<signal.h>
#include<string.h>

int main( int argc , char * argv[] )  {
    char * p = strsignal(SIGTRAP);
    std::cout << p << std::endl;



    return EXIT_SUCCESS;
}

