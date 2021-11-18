//
// Created by soroush on 11/17/21.
//
#include<stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main5(int argc,char *argv[]) {
    char msgFromMain[500], msgFromFinder[500];

    int fifo=0;
    if ((fifo = open(argv[0], O_RDONLY)) < 0) {
        printf("cannot open pipePlacer\n" );
        return -1 ;
    }
    char buf[500] = {0};
    read(fifo, buf, 500);
    close(fifo);
    strcpy(msgFromMain,buf);
    char * finderToPlacer = "/home/soroush/CLionProjects/os_project/findertoplacer";
    if ((fifo = open(finderToPlacer, O_RDONLY)) < 0) {
        printf("cannot open findertoplacer\n" );
        return -1 ;
    }
    char buf2[500] = {0};
    read(fifo, buf2, 500);
    close(fifo);
    strcpy(msgFromFinder,buf);



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
    char strs2[20][300];
    // loop through the string to extract all other tokens
    int count2 =0;
    token = strtok(msgFromFinder, " ");
    while( token != NULL ) {
        strcpy(strs[count2],token);
        printf( " %s\n", strs2[count2] ); //printing each token
        token = strtok(NULL, " ");
        count++;
    }
    for (int i = 0; i <20 ; ++i) {
        strcat(strs[i],strs2[i]);
    }



    if (mkfifo(argv[0], S_IRUSR | S_IWUSR) < 0) {
        printf("finder proccess :Can not create findertoplacer fifo\n");

    }

    //sending first part to decoder named pipe
    // Open FIFO for write only
    int fd = open(argv[0], O_NONBLOCK );
    printf("open kardam \n");
    // Write the input arr2ing on FIFO
    // and close it
    for (int i = 0; i < 20; ++i) {
        printf("%s \t ",strs[i]);
        write(fd, strs[i], strlen(strs[i])+1);
    }

    close(fd);
    printf("placer procces : msg wrote in pipePlacer \n");
    return 0;
}