/*
 * =====================================================================================
 *
 *       Filename:  msgreceive.c
 *
 *    Description:  just for fun
 *
 *        Version:  1.0
 *        Created:  10/22/2015 05:25:46 PM
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
#include<errno.h>
#include<sys/msg.h>

#define BUFSIZE 512

struct msg_st
{
  long int msg_type;
  char text[BUFSIZE];
};

int main(int argc , char * argv[])
{
  int running = 1;
  int msgid = -1;
  struct msg_st data;
  long int msgtype = 0;

  msgid = msgget((key_t)1234 , 0666 | IPC_CREAT);
  if(msgid == -1)  {
    fprintf(stderr , "msgget failed with error: %d\n" , errno);
    exit(EXIT_FAILURE);
  }
  
  while(running)  {
    if(msgrcv(msgid , (void*)&data , BUFSIZE , msgtype , 0) == -1)  {
      fprintf(stderr , "msgrcv failed with errno : %d\n" , errno);
      exit(EXIT_FAILURE);
    }
    printf("you wrote : %s\n",data.text);
    if(strncmp(data.text , "end" , 3) == 0)  {
      running = 0;
    }
  }
  
  if(msgctl(msgid , IPC_RMID , 0) == -1) {
    fprintf(stderr , "msgctl (ICP_RMID) failed\n");
    exit(EXIT_FAILURE);
  }
  return EXIT_SUCCESS;
}
