# Operating-System-CSE3241
Question solve RU CSE
#define _GNU_SOURCE
#include<stdio.h>
#include<pthread.h>
#include <sys/syscall.h>
#include<sched.h>
#include<unistd.h>
cpu_set_t mask;

int main(){

    int pid,tid,cpu,no;
    pid = getpid();
    tid = syscall(SYS_gettid);
    cpu = sched_getcpu();
    printf("PID : %d TID: %d CPU :%d \n",pid,tid,cpu);

    int cpuNo = sysconf(_SC_NPROCESSORS_ONLN);
    printf("No. of available CPUS: %d\n", cpuNo);
    printf("Cpu Affinity : ");
    sched_getaffinity(0,sizeof(cpu_set_t),&mask);
    for(int i = 0;i<cpuNo;i++)
        printf("%d ",CPU_ISSET(i,&mask));
    printf("\n");

    printf("Schedular algo %s \n",sched_getscheduler(pid) == SCHED_FIFO ? "FIFO" : "RR");

    CPU_ZERO(&mask);
    CPU_SET(5,&mask);
    sched_setaffinity(0,sizeof(cpu_set_t),&mask);
    cpu = sched_getcpu();
    printf("After PID : %d TID: %d CPU :%d \n",pid,tid,cpu);

    struct sched_param sp = {.sched_priority = 80};
    sched_setscheduler(0,SCHED_FIFO,&sp);
    printf("After Schedular algo %s \n",sched_getscheduler(pid) == SCHED_FIFO ? "FIFO" : "RR");

    return 0;
}
