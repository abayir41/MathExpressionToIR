#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Structures.h"

void writeAllocation(const char* variableName);
void writeStore(const char* variableName,const char* value);
void writeToFile(const char line[]);

struct VariableStruct* variables;
int variableCount = 0;

void disposeVariables(){
    free(variables);
}

bool checkIfVariableExist(const char* name)
{
    for(int i = 0; i < variableCount; i++)
    {
        if(strcmp(variables[i].variableName, name) == 0) {
            return true;
        }
    }

    return false;
}

void setVariableValue(const char* name, const char* value)
{
    //if it is not initialized, then initialize
    if(variableCount == 0)
    {
        variables = (struct VariableStruct*) malloc(sizeof(struct VariableStruct));
        strcpy(variables->variableName, name);
        variableCount++;

        writeAllocation(name);
        writeStore(name, value);

        return;
    }

    //iterate it untill find the variable
    for(int i = 0; i < variableCount; i++)
    {
        if(strcmp(variables[i].variableName, name) == 0)
	    {
            writeStore(name, value);
            return;
	    }
    }

    //if it is not found, then create new variable and assign it to
    variableCount++;
    variables = (struct VariableStruct*) realloc(variables, variableCount * sizeof(struct VariableStruct));
    strcpy(variables[variableCount - 1].variableName, name);

    writeAllocation(name);
    writeStore(name, value);
}

void writeAllocation(const char* variableName)
{
    writeToFile("%");
    writeToFile(variableName);
    writeToFile(" = alloca i32");
    writeToFile("\n");
}

void writeStore(const char* variableName,const char* value)
{
    writeToFile("store i32 ");
    writeToFile(value);
    writeToFile(", i32* ");
    writeToFile("%");
    writeToFile(variableName);
    writeToFile("\n");
}