#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Structures.h"
#include "VariableController.h"
#include "ProcessCounter.h"


void writeToFile(char line[]);

char* getVarProcessName(){
    char* result = (char*) calloc(257 , sizeof(char));
    result[0] = '%';
    result[1] = '%';
    char snum[256];
    snprintf(snum, sizeof(snum), "%d", getProcessCount());
    strcat(result,snum);
    return result;
}


void writeAProcessToFile(char* variableName, char* processName, char* leftSide, char* rightSide);

//Pretty straightforward calculate function. Take root of tree and calculate it recursively. When find any number or variable return their values.
char* calculate(const struct Node* startPoint){

    if (startPoint->Type == BitAnd)
    {
        char* left = calculate(startPoint->Left);
        char* right = calculate(startPoint->Right);

        char* assignedVariableName = getVarProcessName();
        writeAProcessToFile(assignedVariableName, "and", left, right);

        //free(left);
        //free(right);

        return assignedVariableName;
    }

    if (startPoint->Type == BitOr)
    {
        char* left = calculate(startPoint->Left);
        char* right = calculate(startPoint->Right);

        char* assignedVariableName = getVarProcessName();
        writeAProcessToFile(assignedVariableName, "or", left, right);

        //free(left);
        //free(right);

        return assignedVariableName;
    }

    if (startPoint->Type == Plus)
    {
        char* left = calculate(startPoint->Left);
        char* right = calculate(startPoint->Right);

        char* assignedVariableName = getVarProcessName();
        writeAProcessToFile(assignedVariableName, "add", left, right);

        //free(left);
        //free(right);

        return assignedVariableName;
    }

    if (startPoint->Type == Minus)
    {
        char* left = calculate(startPoint->Left);
        char* right = calculate(startPoint->Right);

        char* assignedVariableName = getVarProcessName();
        writeAProcessToFile(assignedVariableName, "sub", left, right);

        //free(left);
        //free(right);

        return assignedVariableName;
    }

    if (startPoint->Type == Multiply)
    {
        char* left = calculate(startPoint->Left);
        char* right = calculate(startPoint->Right);

        char* assignedVariableName = getVarProcessName();
        writeAProcessToFile(assignedVariableName, "mul", left, right);

        //free(left);
        //free(right);

        return assignedVariableName;
    }

    if (startPoint->Type == Modulo)
    {
        char* left = calculate(startPoint->Left);
        char* right = calculate(startPoint->Right);

        char* assignedVariableName = getVarProcessName();
        writeAProcessToFile(assignedVariableName, "srem", left, right);

        //free(left);
        //free(right);

        return assignedVariableName;
    }

    if (startPoint->Type == Divide)
    {
        char* left = calculate(startPoint->Left);
        char* right = calculate(startPoint->Right);

        char* assignedVariableName = getVarProcessName();
        writeAProcessToFile(assignedVariableName, "sdiv", left, right);

        //free(left);
        //free(right);

        return assignedVariableName;
    }

    if (startPoint->Type == TwoParameterFunction)
    {
        char* left = calculate(startPoint->Left);
        char* right = calculate(startPoint->Right);

        if(strcmp(startPoint->FuncName, "xor") == 0)
        {
            char* assignedVariableName = getVarProcessName();
            writeAProcessToFile(assignedVariableName, "xor", left, right);

            //free(left);
            //free(right);

            return assignedVariableName;
        }

        if(strcmp(startPoint->FuncName, "ls") == 0)
        {
            char* assignedVariableName = getVarProcessName();
            writeAProcessToFile(assignedVariableName, "shl", left, right);

            //free(left);
            //free(right);

            return assignedVariableName;
        }

        if(strcmp(startPoint->FuncName, "rs") == 0)
        {
            char* assignedVariableName = getVarProcessName();
            writeAProcessToFile(assignedVariableName, "ashr", left, right);

            //free(left);
            //free(right);

            return assignedVariableName;
        }

        if(strcmp(startPoint->FuncName, "lr") == 0)
        {
            //todo: implement it
            char* assignedVariableName = getVarProcessName();
            writeAProcessToFile(assignedVariableName, "BROOOO", left, right);

            //free(left);
            //free(right);

            return assignedVariableName;
        }

        if(strcmp(startPoint->FuncName, "rr") == 0)
        {
            //todo: implement it
            char* assignedVariableName = getVarProcessName();
            writeAProcessToFile(assignedVariableName, "BROOOO", left, right);

            //free(left);
            //free(right);

            return assignedVariableName;
        }

        return "error";
    }

    if (startPoint->Type == OneParameterFunction)
    {

        char* value = calculate(startPoint->SingleChild);

        char* assignedVariableName = getVarProcessName();
        writeAProcessToFile(assignedVariableName, "xor", value, "-1");

        //free(value);

        return assignedVariableName;
    }

    if(startPoint->Type == Number)
    {
        return startPoint->Number;
    }

    if(startPoint->Type == Variable)
    {

        if(!checkIfVariableExist(startPoint->VariableName))
        {
            //Throw hata
            return "";
        }

        char* result = getVarProcessName();
        writeToFile(result);
        writeToFile(" = ");
        writeToFile("load i32, i32*");
        writeToFile(" %%");
        writeToFile(startPoint->VariableName);
        writeToFile("\n");

        return result;
    }
}

void writeAProcessToFile(char* variableName, char* processName, char* leftSide, char* rightSide)
{
    writeToFile(variableName);
    writeToFile(" = ");
    writeToFile(processName);
    writeToFile(" i32 ");
    writeToFile(leftSide);
    writeToFile(", ");
    writeToFile(rightSide);
    writeToFile("\n");
}