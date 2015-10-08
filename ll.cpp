/*************************************************************************
  > File Name: ll.cpp
  > Author: lewin
  > Mail: lilinhan1303@gmail.com
  > Company:  Xiyou Linux Group
  > Created Time: Tue 29 Sep 2015 14:44:08 CST
 ************************************************************************/

#include<iostream>
#include<string>
#include<cstdlib>
#include<cerrno>
#include<sys/types.h>
#include<dirent.h>
#include<string>
#include<sys/stat.h>
#include<string.h>
#include<assert.h>
#include<unistd.h>
#include<pwd.h>
#include<grp.h>
#include<time.h>

class LL {
    private:
        DIR * dir;
        struct dirent * file;
        struct stat sb;
        std::string FileName;

    public:
        LL(std::string name):FileName(name)  {}
        ~LL() {}

        void JudgeTheFileTape()  {
            if(S_ISREG(sb.st_mode))  {
                std::cout << "-" ;
            }
            else if( S_ISDIR(sb.st_mode)) {
                std::cout << "d" ;
            }
            else if( S_ISCHR(sb.st_mode))  {
                std::cout << "c";
            }
            else if(S_ISBLK(sb.st_mode))  {
                std::cout << "b";
            }
            else if (S_ISFIFO(sb.st_mode))  {
                std::cout << "p";
            }
            else if(S_ISLNK(sb.st_mode))  {
                std::cout << "l";
            }
            else if (S_ISSOCK(sb.st_mode))  {
                std::cout << "s";
            }
        }

        void PrintFilePermission()  {
            //check user permissions
            if( sb.st_mode & S_IRUSR ) {
                std::cout << "r";
            } else {
                std::cout << "-" ;
            }
            if( sb.st_mode & S_IWUSR )  {
                std::cout << "w";
            }else {
                std::cout << "-";
            }
            if( sb.st_mode & S_IXUSR )  {
                std::cout << "x";
            }else  {
                std::cout << "-";
            }

            //check group permissions
            if( sb.st_mode & S_IRGRP ) {
                std::cout << "r";
            }else {
                std::cout << "-";
            }
            if( sb.st_mode & S_IWGRP )  {
                std::cout << "w";
            }else {
                std::cout << "-";
            }
            if( sb.st_mode & S_IXGRP )  {
                std::cout << "x";
            }else {
                std::cout << "-";
            }

            //check other permissions
            if( sb.st_mode & S_IROTH )  {
                std::cout << "r";
            }else {
                std::cout << "-";
            }
            if( sb.st_mode & S_IWOTH )  {
                std::cout << "w";
            }else {
                std::cout << "-";
            }
            if( sb.st_mode & S_IXOTH )  {
                std::cout << "x";
            }else {
                std::cout << "-";
            }
            std::cout << " ";
        }

        void PrintFileHardLink()  {
            std::cout << sb.st_nlink << " ";
        }

        void PrintFileUserAndFileGroup()  {
            struct passwd * pw_str;
            struct group * gp;
            //write file user;
            if((pw_str = getpwuid(sb.st_uid)) == NULL)  {
                std::cout << sb.st_uid << " ";
            }else{
                std::cout << pw_str->pw_name << " ";
            }
            //write file group
            if((gp = getgrgid( sb.st_gid )) == NULL )  {
                std::cout << sb.st_gid << " ";
            }else {
                std::cout << gp->gr_name << " ";
            }

        }

        void PrintSizeAndTime() {
            time_t Time = sb.st_mtime;
            std::cout << sb.st_size << " ";
            std::cout << asctime(gmtime(&Time)) <<" ";
        }

        void PrintAllFile() {
            if((dir = opendir(FileName.c_str())) == NULL){
                std::cout << "open directory is error!" << std::endl;
                exit(0);
            }
            while((file = readdir(dir)) != NULL)  {
                if(file->d_name[0] == '.')  {  // Don't print the .* file
                    continue;
                }
                if( -1 == stat(file->d_name , &sb))  {  //file stat into sb
                    std::cout << " stat is error!" << std::endl;
                    exit(0);
                }

                JudgeTheFileTape();
                PrintFilePermission();
                PrintFileHardLink();
                PrintFileUserAndFileGroup();
                PrintSizeAndTime();
                std::cout << file->d_name << std::endl;
            }
        }
};



int main( int argc , char * argv[] )  {
    assert(argc == 1);
    char path[100];
    getcwd(path,sizeof(path));
    std::cout << path << std::endl;
    LL l(path);
    l.PrintAllFile();
    return EXIT_SUCCESS;
}

