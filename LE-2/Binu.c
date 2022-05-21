#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc , char *argv[]){
    char *pipePath , msg[50] , *terMsg;
    int fd;

    terMsg = "BIDAY";
    pipePath = argv[1];
   
    while(1){
        fd = open(pipePath,O_RDONLY);
        read(fd,msg,sizeof(msg));
        close(fd);
        printf("%s\n",msg);
        if(strcmp(msg,"BYE") == 0){
            fd = open(pipePath,O_WRONLY);
            write(fd,terMsg,strlen(terMsg)+1);
            close(fd);
            break;
        }
    }

    return 0;
}