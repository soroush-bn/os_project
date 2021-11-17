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
int main(int argc,char *argv[]) {
    char msgFromMain[500], msgFromDecoder[500];
    char * token = strtok(msgFromMain, "$");
    char strs[20][300];
    // loop through the string to extract all other tokens
    int count =0;
    while( token != NULL ) {
        strcpy(strs[count],token);
        printf( " %s\n", strs[count] ); //printing each token
        token = strtok(NULL, "###");
        count++;
    }

    for (int i = 0; i < 20 ; ++i) {
        if (strlen(strs[i])>1){
            int index=(int) strs[i][0];
            int length=(int) strs[i][2];
            char* res =find(index,length,msgFromDecoder);
        }
        else{
            continue;
        }
    }


    return 0;
}


