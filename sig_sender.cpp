/*************************************************************************
    > File Name: sig_sender.cpp
    > Author: lewin
    > Mail: lilinhan1303@gmail.com
    > Company:  Xiyou Linux Group
    > Created Time: Fri 09 Oct 2015 09:31:48 CST
 ************************************************************************/

#include<iostream>
#include<string>
#include<cstdlib>
#include<cerrno>
#include<string.h>


int main( int argc , char * argv[] )  {
    int numSigs , sig , j;
    pid_t pid;

    if( argc < 4 || strcmp(argv[1] , "--help") == 0 )  {
        std::cout << argv[0] << "  pid num-sigs sig-num[sig-num-2]" << std::endl;
    }
    pid = getLong(argv[1] , 0 ,"PID");
    numSigs = getInt(argv[2] , GN_GT_0 , "num-sigs");
    sig = getInt(argv[3] , 0 , "sig-num");

    std::cout << argv[0] << ": sending signal " << sig << " to process " << (long)pid << " "  << numSigs << "  times"  << std::endl;

    for( int j = 0 ; j < numSigs ; ++j )  {
        if( kill(pid , sig) == -1)  {
            perror("kill");
            exit(-1);
        }
    }

    if(argc > 4)  {
        if( kill(pid , getInt(argv[4] , 0 , "sig-num-2")) == -1)  {
            perror("kill");
            exit(-1);
        }
    }

    std::cout << argv[0] << ": exiting"  << std::endl;
    return EXIT_SUCCESS;
}

