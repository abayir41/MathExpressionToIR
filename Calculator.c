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

        if(left[0] == '=' || right[0] == '=')
        {
            free(left);
            free(right);
            char* result = (char*) calloc(10 , sizeof(char));
            result[0] = '=';
            return result;
        }

        free(left);
        free(right);

        return assignedVariableName;
    }

    if (startPoint->Type == BitOr)
    {
        char* left = calculate(startPoint->Left);
        char* right = calculate(startPoint->Right);

        char* assignedVariableName = getVarProcessName();
        writeAProcessToFile(assignedVariableName, "or", left, right);


        if(left[0] == '=' || right[0] == '=')
        {
            free(left);
            free(right);
            char* result = (char*) calloc(10 , sizeof(char));
            result[0] = '=';
            return result;
        }


        free(left);
        free(right);

        return assignedVariableName;
    }

    if (startPoint->Type == Plus)
    {
        char* left = calculate(startPoint->Left);
        char* right = calculate(startPoint->Right);

        if(left[0] == '=' || right[0] == '=')
        {
            free(left);
            free(right);
            char* result = (char*) calloc(10 , sizeof(char));
            result[0] = '=';
            return result;
        }

        char* assignedVariableName = getVarProcessName();
        writeAProcessToFile(assignedVariableName, "add", left, right);

        free(left);
        free(right);

        return assignedVariableName;
    }

    if (startPoint->Type == Minus)
    {
        char* left = calculate(startPoint->Left);
        char* right = calculate(startPoint->Right);

        if(left[0] == '=' || right[0] == '=')
        {
            free(left);
            free(right);
            char* result = (char*) calloc(10 , sizeof(char));
            result[0] = '=';
            return result;
        }

        char* assignedVariableName = getVarProcessName();
        writeAProcessToFile(assignedVariableName, "sub", left, right);

        free(left);
        free(right);

        return assignedVariableName;
    }

    if (startPoint->Type == Multiply)
    {
        char* left = calculate(startPoint->Left);
        char* right = calculate(startPoint->Right);

        if(left[0] == '=' || right[0] == '=')
        {
            free(left);
            free(right);
            char* result = (char*) calloc(10 , sizeof(char));
            result[0] = '=';
            return result;
        }

        char* assignedVariableName = getVarProcessName();
        writeAProcessToFile(assignedVariableName, "mul", left, right);

        free(left);
        free(right);

        return assignedVariableName;
    }

    if (startPoint->Type == Modulo)
    {
        char* left = calculate(startPoint->Left);
        char* right = calculate(startPoint->Right);

        if(left[0] == '=' || right[0] == '=')
        {
            free(left);
            free(right);
            char* result = (char*) calloc(10 , sizeof(char));
            result[0] = '=';
            return result;
        }

        char* assignedVariableName = getVarProcessName();
        writeAProcessToFile(assignedVariableName, "srem", left, right);

        free(left);
        free(right);

        return assignedVariableName;
    }

    if (startPoint->Type == Divide)
    {
        char* left = calculate(startPoint->Left);
        char* right = calculate(startPoint->Right);

        if(left[0] == '=' || right[0] == '=')
        {
            free(left);
            free(right);
            char* result = (char*) calloc(10 , sizeof(char));
            result[0] = '=';
            return result;
        }

        char* assignedVariableName = getVarProcessName();
        writeAProcessToFile(assignedVariableName, "sdiv", left, right);

        free(left);
        free(right);

        return assignedVariableName;
    }

    if (startPoint->Type == TwoParameterFunction)
    {
        char* left = calculate(startPoint->Left);
        char* right = calculate(startPoint->Right);

        if(left[0] == '=' || right[0] == '=')
        {
            free(left);
            free(right);
            char* result = (char*) calloc(10 , sizeof(char));
            result[0] = '=';
            return result;
        }

        if(strcmp(startPoint->FuncName, "xor") == 0)
        {
            char* assignedVariableName = getVarProcessName();
            writeAProcessToFile(assignedVariableName, "xor", left, right);

            free(left);
            free(right);

            return assignedVariableName;
        }

        if(strcmp(startPoint->FuncName, "ls") == 0)
        {
            char* assignedVariableName = getVarProcessName();
            writeAProcessToFile(assignedVariableName, "shl", left, right);

            free(left);
            free(right);

            return assignedVariableName;
        }

        if(strcmp(startPoint->FuncName, "rs") == 0)
        {
            char* assignedVariableName = getVarProcessName();
            writeAProcessToFile(assignedVariableName, "ashr", left, right);

            free(left);
            free(right);

            return assignedVariableName;
        }

        if(strcmp(startPoint->FuncName, "lr") == 0)
        {
            char* assignedVariableName = getVarProcessName();
            writeAProcessToFile(assignedVariableName, "shl", left, right);

            char* assignedVariableName2 = getVarProcessName();
            writeAProcessToFile(assignedVariableName2, "sub", "32", right);

            char* assignedVariableName3 = getVarProcessName();
            writeAProcessToFile(assignedVariableName3, "ashr", left, assignedVariableName2);

            char* assignedVariableName4 = getVarProcessName();
            writeAProcessToFile(assignedVariableName4, "or", assignedVariableName, assignedVariableName3);

            free(assignedVariableName);
            free(assignedVariableName2);
            free(assignedVariableName3);
            free(left);
            free(right);

            return assignedVariableName4;
        }

        if(strcmp(startPoint->FuncName, "rr") == 0)
        {
            char* assignedVariableName = getVarProcessName();
            writeAProcessToFile(assignedVariableName, "ashr", left, right);

            char* assignedVariableName2 = getVarProcessName();
            writeAProcessToFile(assignedVariableName2, "sub", "32", right);

            char* assignedVariableName3 = getVarProcessName();
            writeAProcessToFile(assignedVariableName3, "shl", left, assignedVariableName2);

            char* assignedVariableName4 = getVarProcessName();
            writeAProcessToFile(assignedVariableName4, "or", assignedVariableName, assignedVariableName3);

            free(assignedVariableName);
            free(assignedVariableName2);
            free(assignedVariableName3);
            free(left);
            free(right);

            return assignedVariableName4;
        }

        char* result = (char*) calloc(10 , sizeof(char));
        result[0] = '=';
        return result;
    }

    if (startPoint->Type == OneParameterFunction)
    {
        char* value = calculate(startPoint->SingleChild);

        if(value[0] == '=')
        {
            free(value);
            char* result = (char*) calloc(10 , sizeof(char));
            result[0] = '=';
            return result;
        }

        char* assignedVariableName = getVarProcessName();
        writeAProcessToFile(assignedVariableName, "xor", value, "-1");

        free(value);

        return assignedVariableName;
    }

    if(startPoint->Type == Number)
    {
        char* result = (char*) calloc(257 , sizeof(char));
        strcpy(result, startPoint->Number);
        return result;
    }

    if(startPoint->Type == Variable)
    {

        if(!checkIfVariableExist(startPoint->VariableName))
        {
            char* result = (char*) calloc(10 , sizeof(char));
            result[0] = '=';
            return result;
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