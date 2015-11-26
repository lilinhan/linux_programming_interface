/*
 * =====================================================================================
 *
 *       Filename:  msgsender.c
 *
 *    Description:  send message 
 *
 *        Version:  1.0
 *        Created:  10/22/2015 05:39:57 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lewin , lilinhan1303@gmail.com
 *   Organization:  Xiyou Linux Group
 *
 * =====================================================================================
 */

#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sys/msg.h>
#include<errno.h>

#define MAX_TEXT 512
#define BUF_SIZE 512

struct msg_st{
  long int msg_type;
  char text[MAX_TEXT];
};

int main(int argc , char * argv[])
{
  int running = 1;
  struct msg_st data;
  char buffer[BUF_SIZE];
  int msgid = -1;

  msgid = msgget((key_t)1234 , 0666 | IPC_CREAT);
  if(msgid == -1) {
    fprintf(stderr,"msgget failed with errno : %d\n", errno);
    exit(EXIT_FAILURE);
  }

  while(running) {
    printf("Enter song text:");
    fgets(buffer , BUF_SIZE , stdin);
    data.msg_type = 1;
    strcpy(data.text, buffer);

    if(msgsnd(msgid, (void *)&data, MAX_TEXT, 0) == -1)  {
      fprintf(stderr, "msgsnd failed\n");
      exit(EXIT_FAILURE);
    }

    if(strncmp(buffer, "end", 3) == 0) {
      running = 0;
      sleep(1);
    }
  }
  return EXIT_SUCCESS;
}


