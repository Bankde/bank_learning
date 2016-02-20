#include <stdlib.h>
#include <stdio.h>
#include <string.h>     

int main(int argc, char **argv){
    time_t t;
    int offset;
    char* fname;
    char* command;
    char tmp[10];

    fname = (char*) malloc(20);
    command = (char*) malloc(50);

    srand((unsigned) time(&t));
    offset = rand() % 1000;
    snprintf(tmp, 10, "%d", offset);
    strcat(fname, "pass");
    strcat(fname, tmp);
    strcat(fname, ".txt");

    strcpy(command, "touch ");
    strcat(command, fname);
    system(command);

    strcpy(command, "chmod 600 ");
    strcat(command, fname);
    system(command);

    strcpy(command, "echo 'bank12345' >> ");
    strcat(command, fname);
    system(command);

    return 0;
}
