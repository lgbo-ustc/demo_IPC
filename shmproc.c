#include"shmproc.h"


/*
 为了获得共享资源，进程需要执行一下操作：
 （1） 测试控制该资源的信号量。 
  (2)  若此信号量的值为正，则允许进行使用该资源。进程将进号量减1。 
 （3） 若此信号量为0，则该资源目前不可用，进程进入睡眠状态，直至信
       号量值大于0，进程被唤醒，转入步骤（1）。 
 （4） 当进程不再使用一个信号量控制的资源时，信号量值加1。如果此时
       有进程正在睡眠等待此信号量，则唤醒此进程。
*/

/*

 sem_op=0:等待一个信号量释放
 sem_op=n:进程要释放n个资源
 sem_op=-n:进程需要申请-n个资源
*/
int semlock(key_t semid){
	struct sembuf sb;
	sb.sem_num=0;
	sb.sem_op=-1;
	sb.sem_flg=SEM_UNDO;
	return semop(semid,&sb,1);
}

int semunlock(key_t semid){
	struct sembuf sb;
	sb.sem_num=0;
	sb.sem_op=1;
	sb.sem_flg=SEM_UNDO;
	return semop(semid,&sb,1);
}
