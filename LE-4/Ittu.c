#define _GNU_SOURCE
#include <stdio.h>
#include <sys/shm.h>
#include <string.h>
#include <sched.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>
#include "rwcshm.h"

int main(int argc, char const  *argv[]) {
    int x , y , result , shmID;
    sem_t *sem;
    x = atoi(argv[0]);
    y = atoi(argv[1]);

    sem = sem_open("/sem", O_CREAT, 0666, 1);
    sem_wait(sem);

    printf("ITTU Before->PID:%d , CPU_INFO:%d , a = %d , b = %d , result = %d\n",
        getpid(),sched_getcpu(),x,y,read_from_shm());
    result = x + y;
    printf("After x + y : %d\n",result);
    write_to_shm(result);

    sem_post(sem);

    return 0;
}