#ifndef SHMPROC_H
#define SHMPROC_H

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<sys/sem.h>
/*
  shmget(  )  创建一个新的共享内存区段 
              取得一个共享内存区段的描述符 
  shmctl(  )  取得一个共享内存区段的信息 
              为一个共享内存区段设置特定的信息 
              移除一个共享内存区段 
  shmat(  )   挂接一个共享内存区段 
  shmdt(  )   于一个共享内存区段的分离
*/


#define KEY_FILE "/tmp/555"
#define THE_SHM_SIZE 4096

struct MUnit{
	int s;
	int c;
};


int semlock(key_t semid);

int semunlock(key_t semid);

#endif

