#define _GNU_SOURCE
#include <stdio.h>
#include <sys/shm.h>
#include <string.h>
#include <sched.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "rwcshm.h"

int main(){
    int x , y , ans = 0;
    pid_t ittu , bittu , mittu;
    char arg1[30] , arg2[30];

    scanf("%d%d",&x,&y);
    sprintf(arg1,"%d",x);
    sprintf(arg2,"%d",y);

    write_to_shm(ans);
  
    ittu = fork();
    if(ittu == 0){
        execlp("./Ittu",arg1,arg2,NULL);
    }
    else{
        bittu = fork();
        if(bittu == 0)
            execlp("./Bittu",arg1,arg2,NULL);
        else{
            mittu = fork();
            if(mittu == 0)
                execlp("./Mittu",arg1,arg2,NULL);
            else{
              
                waitpid(ittu,NULL,0);
                waitpid(bittu,NULL,0);
                waitpid(mittu,NULL,0);
                printf("Parent Process>PID:%d , CPU_INFO:%d , a = %d , b = %d , result = %d\n",
                    getpid(),sched_getcpu(),x,y,read_from_shm());
            }

        }
    }
    return 0;
}