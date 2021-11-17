
#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

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
    char * pipeFileDecoder = "/home/soroush/CLionProjects/ospr1/pipeFileDecoder";

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
    fd = open(pipeFileDecoder, O_NONBLOCK);

    // Read from FIFO
    char arr1[500];
    read(fd, arr1, sizeof(strs[0]));

    // Print the read message
    printf("User2: %s\n", arr1);
    close(fd);
    return 0;
}