#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>

int ans;
pthread_mutex_t key;
int nums[2];

void *sum(void *input){
    pthread_mutex_lock(&key);
    int *x,ans;
    x = input;
    ans = x[0] + x[1];
    printf("In Sum->PID:%d,TID:%d,CPU_INFO:%d,Result:%d\n",getpid(),gettid(),sched_getcpu(),ans);
    if(ans == 100)
        pthread_kill(pthread_self(),SIGUSR1);
    pthread_mutex_unlock(&key);
}
void *sub(void *input){
    pthread_mutex_lock(&key);
    int *x,ans;
    x = input;
    ans = x[0] - x[1];
    printf("In Sub->PID:%d,TID:%d,CPU_INFO:%d,Result:%d\n",getpid(),gettid(),sched_getcpu(),ans);
    if(ans == 100)
        pthread_kill(pthread_self(),SIGUSR1);
    pthread_mutex_unlock(&key);
}
void *mul(void *input){
    pthread_mutex_lock(&key);
    int *x,ans;
    x = input;
    ans = x[0] * x[1];
    printf("In Mul->PID:%d,TID:%d,CPU_INFO:%d,Result:%d\n",getpid(),gettid(),sched_getcpu(),ans);
    if(ans == 100)
        pthread_kill(pthread_self(),SIGUSR1);
    pthread_mutex_unlock(&key);
}

int main(){
    pthread_t Ittu,Bittu,Mittu;
    int tdStatus , a , b , i;
    scanf("%d%d",&nums[0],&nums[1]);

    if(pthread_mutex_init(&key,NULL) != 0){
        printf("Mutex lock intialization is falied\n");
        exit(-1);
    }

    for(i = 0 ;  i < 100 ; i++){
        pthread_create(&Ittu,NULL,sum,(void *)nums);
        pthread_create(&Bittu,NULL,sub,(void *)nums);
        pthread_create(&Mittu,NULL,mul,(void *)nums);
    }
    pthread_join(Ittu,NULL);
    pthread_join(Bittu,NULL);
    pthread_join(Mittu,NULL);

    return 0;
}