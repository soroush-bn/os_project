//
// Created by soroush on 11/17/21.
//
#include<stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc,char *argv[]) {
    char msgFromMain[500], msgFromFinder[500];
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
    token = strtok(msgFromFinder, "\n");
    while( token != NULL ) {
        strcpy(strs[count2],token);
        printf( " %s\n", strs2[count2] ); //printing each token
        token = strtok(NULL, "\n");
        count++;
    }
    for (int i = 0; i <20 ; ++i) {
        strcat(strs[i],strs2[i]);
    }
    return 0;
}