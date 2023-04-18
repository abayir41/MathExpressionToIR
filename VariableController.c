#include <stdlib.h>
#include <string.h>
#include "Structures.h"

struct VariableStruct* variables;
int variableCount = 0;

void disposeVariables(){
    free(variables);
}

long long getVariableValue(const char* name)
{


    //if it is not initialized, then initialize
    if(variableCount == 0)
    {
        variables = (struct VariableStruct*) malloc(sizeof(struct VariableStruct));
        variables->value = 0;
        strcpy(variables->variableName, name);
        variableCount++;
        return 0;
    }

    //iterate it untill find the variable
    for(int i = 0; i < variableCount; i++)
    {
        if(strcmp(variables[i].variableName, name) == 0)
            return variables[i].value;
    }

    //if it is not found, then create new variable and assign it to 0
    variableCount++;
    variables = (struct VariableStruct*) realloc(variables, variableCount * sizeof(struct VariableStruct));
    variables[variableCount - 1].value = 0;
    strcpy(variables[variableCount - 1].variableName, name);
    return 0;

}

void setVariableValue(const char* name, long long value)
{

    //if it is not initialized, then initialize
    if(variableCount == 0)
    {
        variables = (struct VariableStruct*) malloc(sizeof(struct VariableStruct));
        variables->value = value;
        strcpy(variables->variableName, name);
        variableCount++;
        return;
    }

    //iterate it untill find the variable
    for(int i = 0; i < variableCount; i++)
    {
        if(strcmp(variables[i].variableName, name) == 0)
	  {
	  	variables[i].value = value;
		return;
	  }
    }

    //if it is not found, then create new variable and assign it to
    variableCount++;
    variables = (struct VariableStruct*) realloc(variables, variableCount * sizeof(struct VariableStruct));
    variables[variableCount - 1].value = value;
    strcpy(variables[variableCount - 1].variableName, name);
    return;

}