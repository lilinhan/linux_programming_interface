/*************************************************************************
    > File Name: aio.c
    > Author: lewin
    > Mail: lilinhan1303@gmail.com
    > Company:  Xiyou Linux Group
    > Created Time: Mon 19 Oct 2015 18:07:53 CST
 ************************************************************************/

#include<sys/types.h>
#include<sys/stat.h>
#include<limits.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<signal.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<aio.h>
#include<sys/epoll.h>
#include<fcntl.h>
static const size_t BUF_SIZE = 512 * 1024;

volatile int ret;

int fds[2];

void aio_completion_handler( sigval_t sigval)  {
    struct aiocb * req;
    req = (struct aiocb *)sigval.sival_ptr;

    printf("begin ret in handler:%d\n" , ret);

    if(aio_error( req ) == 0)  {
        ret = aio_return( req );
    }else {
        perror("read error");
    }

    printf("end ret in handler: %d\n" , ret);
    write(fds[1] , "hello world!\n" , 13);
    return ;
}

void setup_io()  {
    char INPUTFILE[] = "inputfile";
    int fin = open(INPUTFILE , O_RDONLY);
    if( fin == -1 )  {
        perror("open file error");
    }
    int fd = fin;

    int ret;
    struct aiocb my_aiocb;

    bzero((char *)&my_aiocb , sizeof(struct aiocb));

    my_aiocb.aio_fildes = fd;
    my_aiocb.aio_buf = malloc(BUF_SIZE + 1);
    my_aiocb.aio_nbytes = BUF_SIZE;
    my_aiocb.aio_offset = 0;
    my_aiocb.aio_sigevent.sigev_notify = SIGEV_THREAD;
    my_aiocb.aio_sigevent.sigev_notify_function = aio_completion_handler;
    my_aiocb.aio_sigevent.sigev_notify_attributes = NULL;
    my_aiocb.aio_sigevent.sigev_value.sival_ptr = &my_aiocb;

    ret = aio_read( &my_aiocb );
}

int main(int argc , char * argv[])  {
    if(pipe(fds) == 1)  return -1;

    int epollfd = epoll_create(10);
    struct epoll_event * event = new epoll_event;
    event->events = EPOLLIN;
    event->data.fd = fds[0];

    int n;
    n = epoll_ctl(epollfd , EPOLL_CTL_ADD , fds[0] , event);
    printf("n = %d\n" , n);

    setup_io();
    //sleep(1);

    epoll_event events[10];
    int nfds = epoll_wait(epollfd , events , 10 , -1);
    printf("nfds = %d\n" , nfds);
    for(int i = 0 ; i < nfds ; ++i )  {
        epoll_event ev = events[i];
        if(ev.events & EPOLLIN)  {
            printf("fd %d , event EPOLLIN\n" , ev.data.fd);
        }
        if(ev.events & EPOLLOUT)  {
            printf("fd %d , event EPOLLOUT \n" , ev.data.fd);
        }
        if(ev.events & EPOLLHUP)  {
            printf("fd %d , event EPOLLHUP\n" , ev.data.fd);
        }
        if(ev.events & EPOLLERR)  {
            printf("fd %d , event EPOLLERR\n" , ev.data.fd);
        }
    }
    //sleep(1);
    printf("ret = %d!!!\n",ret);
    return EXIT_SUCCESS;
}

