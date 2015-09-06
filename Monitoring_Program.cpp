/*************************************************************************
    > File Name: Monitoring_Program.cpp
    > Author: lewin
    > Mail: lilinhan1303@gmail.com
    > Company:  Xiyou Linux Group
    > Created Time: 2015年09月06日 星期日 21时06分53秒
 ************************************************************************/

#include<iostream>
#include<string>
#include<cstdlib>
#include<cerrno>
#include<fstream>
int main( int argc , char * argv[] )  {
    char buf[256];
    std::ifstream f("/proc/meminfo",std::ios::in);
    while( !f.eof()) {
        f.getline(buf,sizeof(buf));
        std::cout << buf << std::endl;
    }
    return EXIT_SUCCESS;
}

