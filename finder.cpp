//
// Created by soroush on 11/17/21.
//

#include <stdio.h>
#include <string.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
char* find(int position,int length,char* msg){

    char res[100]="";

    for (int i=position; i <position+length ; ++i) {
        strcat(res, reinterpret_cast<const char *>(msg[i]));
    }
    return res;
}
int main4(int argc,char *argv[]) {
    char msgFromMain[500], msgFromDecoder[500];
    int fifo=0;
    if ((fifo = open(argv[0], O_RDONLY)) < 0) {
        printf("cannot open pipeFinder\n" );
        return -1 ;
    }
    char buf[500] = {0};
    read(fifo, buf, 500);
    close(fifo);
    strcpy(msgFromMain,buf);
    char * decoderToFinder = "/home/soroush/CLionProjects/os_project/decoderToFinder";
    if ((fifo = open(decoderToFinder, O_RDONLY)) < 0) {
        printf("cannot open decoderToFinder\n" );
        return -1 ;
    }
    char buf2[500] = {0};
    read(fifo, buf2, 500);
    close(fifo);
    strcpy(msgFromDecoder,buf);

    char * token = strtok(msgFromMain, "$");
    char strs[20][300];
    // loop through the string to extract all other tokens
    int count =0;
    while( token != NULL ) {
        strcpy(strs[count],token);
        printf( " %s\n", strs[count] ); //printing each token
        token = strtok(NULL, "$");
        count++;
    }
    char res[100]="";
    for (int i = 0; i < 20 ; ++i) {
        if (strlen(strs[i])>1){
            int index=(int) strs[i][0];
            int length=(int) strs[i][2];
            strcat(res,find(index,length,msgFromDecoder));
        }
        else{
            continue;
        }
    }

    char * finderToPlacer= "/home/soroush/CLionProjects/os_project/Findertoplacer";

    if (mkfifo(finderToPlacer, S_IRUSR | S_IWUSR) < 0) {
        printf("finder proccess :Can not create findertoplacer fifo\n");

    }

    //sending first part to decoder named pipe
    // Open FIFO for write only
    int fd = open(finderToPlacer, O_NONBLOCK );
    printf("open kardam \n");
    // Write the input arr2ing on FIFO
    // and close it
    write(fd, res, strlen(res)+1);
    close(fd);
    printf("finder procces : msg wrote in findertoplacer \n");
    return 0;
}


