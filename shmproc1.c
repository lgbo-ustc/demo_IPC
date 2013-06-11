#include"shmproc.h"


int main(){
	/*由proc1创建一个文件*/
	FILE* fp=fopen(KEY_FILE,"w+");
	if(fp<=0){
		printf("fopen error\n");
		exit(1);
	}
	fclose(fp);
	
	key_t shmkey,semkey;
	int shmid,semid;
	struct MUnit *pool=NULL;
	union semun{
		int val;
		struct semid_ds *buf;
		unsigned short *array;
		struct seminfo *__buf;
	} semopts;
	printf("process 1 is running ...\n");
	/*
	 获取key值
	 */
	shmkey=ftok(KEY_FILE,0);
	semkey=ftok(KEY_FILE,0);
	printf("shmkey %d, semkey %d\n",shmkey,semkey);
	/*
	 获取一块大小为THE_SHM_SIZE的共享内存，THE_SHM_SIZE必须
	 为系统内存分页的整数倍
	 */
	shmid=shmget(shmkey,THE_SHM_SIZE,IPC_CREAT|0666);
	if(shmid<=0){
		printf("shmget error\n");
		exit(1);
	}
	/*第二个参数是表示获取的信号量集合中有多少个信号量*/
	semid=semget(semkey,1,IPC_CREAT|0666);
	if(semid<=0){
		printf("semget error\n");
		exit(1);
	}
	/*
	 将semid中的第0个信号量设置为最多只能由1个进程访问
	 */
	semopts.val=1;
	if(semctl(semid,0,SETVAL,semopts)<0){
		printf("semctl error\n");
		goto SEMSETUP;
	}
	printf("create a shared block,id : %d\n",shmid);
	printf("create a semphore, id : %d\n",semid);
	/*
	 挂载共享内存
	 */
	pool=(struct MUnit*)shmat(shmid,NULL,0);
	if(pool==-1){
		printf("shmat error\n");
		goto SEMSETUP;
	}
	int i=0;
	while(i++<30){
		semlock(semid);
		pool->s=random()%100;
		printf("proc 1 write %d,proc 2 write %d\n",pool->s,pool->c);
		semunlock(semid);
		sleep(3);
	}
SEMSETUP:
	if(shmdt(pool)==-1){
		printf("shmdt error\n");
	}
	if(semctl(semid,0,IPC_RMID,0)==-1){
		printf("semctl rm error\n");
	}
	if(shmctl(shmid,IPC_RMID,NULL)==-1){
		printf("shmctl rm error\n");
	}
	return 0;
}
