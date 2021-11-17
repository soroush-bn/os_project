
#include <stdio.h>
#include <string.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int main() {
    char string[1000] = "Hello! We are learning about strto jhgj jhjh gfyf gfhg ### \n 1 2$3 4 ### \n sdf $s dsfasdf $s";
    // Extract the first token
    char * token = strtok(string, "###");
    char strs[3][300];
    // loop through the string to extract all other tokens
    int count =0;
    while( token != NULL ) {
        strcpy(strs[count],token);
        printf( " %s\n", strs[count] ); //printing each token
        token = strtok(NULL, "###");
        count++;
    }
    printf("this is value of first part %s \n",strs[0]);
    int fd;

    // FIFO file path
    char * pipeFileDecoder = "/home/soroush/CLionProjects/os_project/pipeFileDecoder";

    // Creating the named file(FIFO)
    // mkfifo(<pathname>, <permission>)
    mkfifo(pipeFileDecoder, 0666);

    //sending first part to decoder named pipe
    // Open FIFO for write only
    fd = open(pipeFileDecoder, O_NONBLOCK );
    printf("open kardam \n");
//    // Take an input arr2ing from user.
//    // 80 is maximum length
//    fgets(arr2, 80, stdin);

    // Write the input arr2ing on FIFO
    // and close it
    write(fd, strs[0], strlen(strs[0])+1);
    close(fd);
    // Open FIFO for Read only
    //fd = open(pipeFileDecoder, O_NONBLOCK);

    // Read from FIFO
//    char arr1[500];
//    read(fd, arr1, sizeof(strs[0])+1);
//
//    // Print the read message
//    printf("User2: %s\n", arr1);
//    close(fd);

    char *my_args[5];
    pid_t pid;

    my_args[0] = "child.exe";
    my_args[1] = "arg1";
    my_args[2] = "arg2";
    my_args[3] = NULL;

    puts ("fork()ing");

    switch ((pid = fork()))
    {
        case -1:
            /* Fork() has failed */
            perror ("fork");
            break;
        case 0:
            /* This is processed by the child */
            execv ("child.exe", my_args);
            puts("Uh oh! If this prints, execv() must have failed");
            exit(EXIT_FAILURE);
            break;
        default:
            /* This is processed by the parent */
            puts ("This is a message from the parent");
            break;
    }
    return 0;
}