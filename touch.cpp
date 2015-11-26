/*************************************************************************
    > File Name: touch.cpp
    > Author: lewin
    > Mail: lilinhan1303@gmail.com
    > Company:  Xiyou Linux Group
    > Created Time: Tue 29 Sep 2015 14:44:23 CST
 ************************************************************************/

#include<iostream>
#include<string>
#include<cstdlib>
#include<cerrno>
#include<string>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<dirent.h>
#include<assert.h>
#include<unistd.h>

class Touch {
    private:
        std::string FileName;

    public:
        Touch(std::string name):FileName(name) {}
        ~Touch() {}

        void CreateFile ()  {
            int fd = open(FileName.c_str() , O_RDWR | O_EXCL | O_CREAT , 0666);
            assert(fd);
            close(fd);
        }
};

int main( int argc , char * argv[] )  {
    assert(argc==2);
    Touch t(argv[1]);
    t.CreateFile();

    return EXIT_SUCCESS;
}

