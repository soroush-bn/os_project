
#include <stdio.h>
#include <string.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int main3() {
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
    int fd=0;

    // FIFO file path
    char * pipeFileDecoder = "/home/soroush/CLionProjects/os_project/pipeFileDecoder";

    // Creating the named file(FIFO)
    // mkfifo(<pathname>, <permission>)
    if (mkfifo(pipeFileDecoder, S_IRUSR | S_IWUSR) < 0) {
        printf("Can not create pipeFileDecoder fifo\n");

    }else{
        //sending first part to decoder named pipe
        // Open FIFO for write only
        fd = open(pipeFileDecoder, O_NONBLOCK );
        // Write the input arr2ing on FIFO
        // and close it
        write(fd, strs[0], strlen(strs[0])+1);
        close(fd);
        printf("first part write \n");
    }

    // FIFO file path
    char * pipeFileFinder = "/home/soroush/CLionProjects/os_project/pipeFileFinder";

    // Creating the named file(FIFO)
    // mkfifo(<pathname>, <permission>)
    if (mkfifo(pipeFileFinder, S_IRUSR | S_IWUSR) < 0) {
        printf("Can not create pipeFileFinder fifo\n");

    }else{
        //sending first part to decoder named pipe
        // Open FIFO for write only
        fd = open(pipeFileFinder, O_NONBLOCK );
        // Write the input arr2ing on FIFO
        // and close it
        write(fd, strs[1], strlen(strs[1])+1);
        close(fd);
        printf("second part write !  \n");
    }

    // FIFO file path
    char * pipeFilePlacer = "/home/soroush/CLionProjects/os_project/pipeFilePlacer";

    // Creating the named file(FIFO)
    // mkfifo(<pathname>, <permission>)
    if (mkfifo(pipeFilePlacer, S_IRUSR | S_IWUSR) < 0) {
        printf("Can not create pipeFilePlacer fifo\n");

    }else{
        //sending first part to decoder named pipe
        // Open FIFO for write only
        fd = open(pipeFilePlacer, O_NONBLOCK );
        // Write the input arr2ing on FIFO
        // and close it
        write(fd, strs[2], strlen(strs[2])+1);
        close(fd);
        printf("third part writed !  \n");
    }



    //sending first part to decoder named pipe
    // Open FIFO for write only
    //fd = open(pipeFileDecoder, O_NONBLOCK );
 //   printf("open kardam \n");
//    // Take an input arr2ing from user.
//    // 80 is maximum length
//    fgets(arr2, 80, stdin);


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
    pid_t pid1,pid2,pid3;

    pid1 = fork();
    if (pid1 == 0) {
        printf("decoder process\n");
        //child();
        //exec()
    } else if (pid1 < 0) {
        printf("fork error\n");
        return -1;
    }
//
//    my_args[0] = "child.exe";
//    my_args[1] = "arg1";
//    my_args[2] = "arg2";
//    my_args[3] = NULL;
//
//    puts ("fork()ing");
//
//    switch ((pid = fork()))
//    {
//        case -1:
//            /* Fork() has failed */
//            perror ("fork");
//            break;
//        case 0:
//            /* This is processed by the child */
//            execv ("child.exe", my_args);
//            puts("Uh oh! If this prints, execv() must have failed");
//            exit(EXIT_FAILURE);
//            break;
//        default:
//            /* This is processed by the parent */
//            puts ("This is a message from the parent");
//            break;
//    }
    return 0;
}