/*************************************************************************
    > File Name: rm.cpp
    > Author: lewin
    > Mail: lilinhan1303@gmail.com
    > Company:  Xiyou Linux Group
    > Created Time: Tue 29 Sep 2015 14:44:16 CST
 ************************************************************************/

#include<iostream>
#include<string>
#include<cstdlib>
#include<cerrno>
#include<unistd.h>
#include<string>
#include<assert.h>

class RM{
    private:
        std::string FileName;

    public:
        RM(std::string name) : FileName(name) {}
        ~RM() {}

        void RemoveFile()  {
            if(-1 == remove(FileName.c_str()))  {
                std::cout << "remove error!" << std::endl;
            }
            exit(0);
        }
};

int main( int argc , char * argv[] )  {
    assert(argc == 2);
    RM r(argv[1]);
    r.RemoveFile();
    return EXIT_SUCCESS;
}

