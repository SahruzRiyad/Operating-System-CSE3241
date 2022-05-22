int creat_shared_memory(){
    key_t key;
    int shmID;
    key = ftok("test.c",'x');
    shmID = shmget(key,1024,IPC_CREAT|0666);
    return shmID;
}
int read_from_shm(){
    int *str = shmat(creat_shared_memory(),NULL,0);
    int num = *str;
    shmdt(str);
    return num;
}

void write_to_shm(int x){
    int shmID = creat_shared_memory();
    int *str = shmat(shmID,NULL,0);
    *str = x;
    shmdt(str);
}