/*************************************************************************
    > File Name: open.c
    > Author: lewin
    > Mail: lilinhan1303@gmail.com
    > Company:  Xiyou Linux Group
    > Created Time: Wed 07 Oct 2015 15:04:04 CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<fcntl.h>
#include<string.h>

int main(int argc, char *argv[])
{
    int fd;

    if ((fd = open("./1.text", O_WRONLY | O_CREAT | O_TRUNC, 0777)) < 0) {	//打开文件，得到文件描述符
	fprintf(stderr, "open file error ");
	exit(-1);
    }

    char writedata[100];
    char recvdata[100];

    strcpy(writedata, "Hello world!\n");	//准备要写入文件的数据

    /*
       在这里我们先向目标文件中写入数据
       接下来再从目标文件中读取数据
     */

    if (0 > write(fd, writedata, strlen(writedata) + 1)) {	//给文件写入数据
	printf("write data in file error!\n");
	exit(-1);
    }
    close(fd);			//关闭文件描述符

    if ((fd = open("./1.text", O_RDONLY, 0777)) < 0) {	// 打开文件，得到文件描述符
	printf("open file error!\n");
	exit(-1);
    }
    if (0 > read(fd, &recvdata, 100)) {	//从文件中读取数据保存到recvdata里
	printf("read file error!\n");
	exit(-1);
    }
    printf("%s", recvdata);
    close(fd);			//关闭文件描述符

    return EXIT_SUCCESS;
}
