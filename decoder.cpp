//
// Created by soroush on 11/17/21.
//
#include<stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
int decoder(int argc,char *argv[]) {
    char message[100], ch;
    int i, key;
    int fifo=0;
    if ((fifo = open(argv[0], O_RDONLY)) < 0) {
        printf("cannot open pipeDecoder\n" );
        return -1 ;
    }
    char buf[500] = {0};
    read(fifo, buf, 500);
    close(fifo);
    strcpy(message,buf);
    key = 3;
    for (i = 0; message[i] != '\0'; ++i) {
        ch = message[i];
        if (ch >= 'a' && ch <= 'z') {
            ch = ch - key;
            if (ch < 'a') {
                ch = ch + 'z' - 'a' + 1;
            }
            message[i] = ch;
        } else if (ch >= 'A' && ch <= 'Z') {
            ch = ch - key;
            if (ch < 'A') {
                ch = ch + 'Z' - 'A' + 1;
            }
            message[i] = ch;
        }
    }
    printf("Decrypted message: %s", message);
    int fd;

    // FIFO file path
    char * decoderToFinder = "/home/soroush/CLionProjects/os_project/decoderToFinder";

    // Creating the named file(FIFO)
    // mkfifo(<pathname>, <permission>)
    if (mkfifo(decoderToFinder, S_IRUSR | S_IWUSR) < 0) {
        printf("decoder proccess :Can not create decodertofinder fifo\n");

    }

    //sending first part to decoder named pipe
    // Open FIFO for write only
    fd = open(decoderToFinder, O_NONBLOCK );
    printf("open kardam \n");
//    // Take an input arr2ing from user.
//    // 80 is maximum length
//    fgets(arr2, 80, stdin);

    // Write the input arr2ing on FIFO
    // and close it
    write(fd, message, strlen(message)+1);
    close(fd);
    printf("decoder procces : msg wrote in decodertofinder \n");
    return 0;
}