/*************************************************************************
    > File Name: ouch.cpp
    > Author: lewin
    > Mail: lilinhan1303@gmail.com
    > Company:  Xiyou Linux Group
    > Created Time: 2015年09月03日 星期四 15时02分35秒
 ************************************************************************/

#include<iostream>
#include<string>
#include<cstdlib>
#include<cerrno>
#include<signal.h>
#include<unistd.h>

static void sigHandler(int sig)  {
    std::cout << "Ouch!" << std::endl;
}

int main( int argc , char * argv[] )  {
    int j ;
    if(signal(SIGINT , sigHandler) == SIG_ERR)  {
        std::cout << "signal error" << std::endl;
    }

    for(j = 0 ;; j++)  {
        std::cout << j << std::endl;
        sleep(3);
    }
    return EXIT_SUCCESS;
}

