#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc , char *argv[]){
    char *pipePath , msg[50] , terMsg[50];
    int fd;

    pipePath = argv[1];
    fd = open(pipePath,O_WRONLY);

    sprintf(msg,"%s %d %s %d %s","My Pid:",getpid(),"My Parent Pid:",getppid(),"Hello Binu");
    write(fd,msg,strlen(msg)+1);
    close(fd);

    while(1){

        scanf("%s",msg);
        fd = open(pipePath,O_WRONLY);
        write(fd,msg,strlen(msg)+1);
        close(fd);
        if(strcmp(msg,"BYE") == 0){
            fd = open(pipePath,O_RDONLY);
            read(fd,terMsg,sizeof(terMsg));
            close(fd);
    
            if(strcmp(terMsg,"BIDAY") == 0){
                printf("%s\n",terMsg);
                break;
            }
        }
    }
    
    return 0;
}