// Permission Value
//			    User	Group	Other
//	r: 100 (4) 	4	4	4
//	w: 010 (2)	2	2	2
//	x: 001 (1)	0	0	0
//		=============================
//			    6	6	6

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc , char *argv[]){
    int i , pipeFlag;

    for(i = 1 ; i < argc ; i++){
        if(access(argv[i],F_OK) == 0){
            printf("%s pipe already created\n",argv[i]);
        }
        else{
            pipeFlag = mkfifo(argv[i],0666);//(pipe_path,parmission)
            if(pipeFlag < 0){
                printf("Pipe %s Cannot be created\n",argv[i]);
                exit(-1);
            }
            else
                printf("Pipe %s successfully created\n",argv[i]);
        }
    }

    return 0;
}