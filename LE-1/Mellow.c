#define GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

int main(){
    pid_t cpid_killow , cpid_pillow;
    cpid_killow = fork();

    if(cpid_killow < 0){
        printf("Error! Child Killow Cannot be Created\n");
        return 0;
    }
   
    if(cpid_killow == 0){
        execlp("./Killow","Killow",NULL);
    }
    else{
        cpid_pillow = fork();
        if(cpid_pillow < 0){
            printf("Error! Child Pillow Cannot be Created\n");
            return 0;
        }
        if(cpid_pillow == 0){
            execlp("./Pillow","Pillow",NULL);
        }
        else{
            for(;;)
                printf("Process -%d, Parent of Pillow-%d and Killow-%d,running at CPU-%d\n",getpid(),cpid_pillow,cpid_killow,sched_getcpu());
        }
    }
    return 0;
}
