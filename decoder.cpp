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
    strcpy(message,"salam bar shoma ");
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
    mkfifo(decoderToFinder, 0666);

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
    return 0;
}