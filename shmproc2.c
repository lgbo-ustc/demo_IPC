#include"shmproc.h"

int main(){
	int shmid,semid;
	key_t shmkey,semkey;
	struct MUnit* pool=NULL;
	shmkey=ftok(KEY_FILE,0);
	semkey=ftok(KEY_FILE,0);
	printf("shmkey %d, semkey %d\n",shmkey,semkey);
	shmid=shmget(shmkey,0,0666);
	if(shmid==-1){
		printf("shmget error\n");
		return -1;
	}
	semid=semget(semkey,0,0666);
	if(semid==-1){
		printf("semget error\n");
		return -1;
	}
	pool=(struct MUnit*)shmat(shmid,0,0);
	if(pool<=0){
		printf("shmat error\n");
		return -1;
	}
	int i=0;
	while(i++<10){
		semlock(semid);
		pool->c=random()%100;
		printf("proc 1 write %d,proc 2 write %d\n",pool->s,pool->c);
		semunlock(semid);
		sleep(2);
	}
	if(shmdt(pool)==-1){
		printf("shmdt error\n");
	}
	return 0;
}
