#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int processCount = 0;

int getProcessCount(){
    processCount++;
    return processCount;
}

//it will return like %1, %2 ... like in the homework example
char* getVarProcessName(){
    char* result = (char*) calloc(257 , sizeof(char));
    result[0] = '%';
    char snum[256];
    snprintf(snum, sizeof(snum), "%d", getProcessCount());
    strcat(result,snum);
    return result;
}