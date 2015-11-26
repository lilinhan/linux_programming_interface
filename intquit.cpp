/*************************************************************************
    > File Name: intquit.cpp
    > Author: lewin
    > Mail: lilinhan1303@gmail.com
    > Company:  Xiyou Linux Group
    > Created Time: 2015年09月03日 星期四 15时09分57秒
 ************************************************************************/

#include<iostream>
#include<string>
#include<cstdlib>
#include<cerrno>
#include<unistd.h>
#include<signal.h>

static void sigHandler(int sig)  {
    static int count = 0;
    if(sig == SIGINT)  {
        count++;
        std::cout << "Caught SIGINT " << count << std::endl;
        return;
    }

    std::cout << "Caught SIGQUIT - that's all folks!" << std::endl;
    exit(EXIT_SUCCESS);
}

int main( int argc , char * argv[] )  {
    if(signal(SIGINT , sigHandler) == SIG_ERR)  {
        std::cout << "signal" << std::endl;
    }
    if(signal(SIGQUIT , sigHandler) == SIG_ERR)  {
        std::cout << "SIGNAL" << std::endl;
    }

    while(1)  {
        pause();
    }


    return EXIT_SUCCESS;
}

