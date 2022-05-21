#define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int main(){
    for(;;)
        printf("I am child-%d running at CPU-%d.\n",getpid(),sched_getcpu()); 
    return 0;
}
