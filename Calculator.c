#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Structures.h"
#include "VariableController.h"
void writeToFile(char line[] );
int getProcessCount();
char* getVarProcessName(){
    char result[257] = "%";
    char snum[256];
    itoa(getProcessCount(),snum,10);
    strcat(result,snum);
    return result;
}
//Pretty straightforward calculate function. Take root of tree and calculate it recursively. When find any number or variable return their values.
char* calculate(const struct Node* startPoint){

    if (startPoint->Type == BitAnd)
    {
        char* left = calculate(startPoint->Left);
        char* right = calculate(startPoint->Right);
        char* result = getVarProcessName();
        writeToFile(result);
        writeToFile(" = ");
        writeToFile("and i32 ");
        writeToFile(left);
        writeToFile(",");
        writeToFile(right);
        writeToFile("\n");

        return result;
    }

    if (startPoint->Type == BitOr)
    {
        char* left = calculate(startPoint->Left);
        char* right = calculate(startPoint->Right);
        char* result = getVarProcessName();
        writeToFile(result);
        writeToFile(" = ");
        writeToFile("or i32 ");
        writeToFile(left);
        writeToFile(",");
        writeToFile(right);
        writeToFile("\n");

        return result;
    }

    if (startPoint->Type == Plus)
    {
        char* left = calculate(startPoint->Left);
        char* right = calculate(startPoint->Right);
        char* result = getVarProcessName();
        writeToFile(result);
        writeToFile(" = ");
        writeToFile("add i32 ");
        writeToFile(left);
        writeToFile(",");
        writeToFile(right);
        writeToFile("\n");

        return result;
    }

    if (startPoint->Type == Minus)
    {
        char* left = calculate(startPoint->Left);
        char* right = calculate(startPoint->Right);
        char* result = getVarProcessName();
        writeToFile(result);
        writeToFile(" = ");
        writeToFile("sub i32 ");
        writeToFile(left);
        writeToFile(",");
        writeToFile(right);
        writeToFile("\n");

        return result;
    }

    if (startPoint->Type == Multiply)
    {
        char* left = calculate(startPoint->Left);
        char* right = calculate(startPoint->Right);
        char* result = getVarProcessName();
        writeToFile(result);
        writeToFile(" = ");
        writeToFile("mul i32 ");
        writeToFile(left);
        writeToFile(",");
        writeToFile(right);
        writeToFile("\n");

        return result;
    }

    if (startPoint->Type == Modulo)
    {
        char* left = calculate(startPoint->Left);
        char* right = calculate(startPoint->Right);
        char* result = getVarProcessName();
        writeToFile(result);
        writeToFile(" = ");
        writeToFile("srem i32 ");
        writeToFile(left);
        writeToFile(",");
        writeToFile(right);
        writeToFile("\n");

        return result;
    }

    if (startPoint->Type == Divide)
    {
        char* left = calculate(startPoint->Left);
        char* right = calculate(startPoint->Right);
        char* result = getVarProcessName();
        writeToFile(result);
        writeToFile(" = ");
        writeToFile("sdiv i32 ");
        writeToFile(left);
        writeToFile(",");
        writeToFile(right);
        writeToFile("\n");

        return result;
    }

    if (startPoint->Type == TwoParameterFunction)
    {
        char* left = calculate(startPoint->Left);
        char* right = calculate(startPoint->Right);

        if(strcmp(startPoint->FuncName, "xor") == 0)
        {

            char* result = getVarProcessName();
            writeToFile(result);
            writeToFile(" = ");
            writeToFile("xor i32 ");
            writeToFile(left);
            writeToFile(",");
            writeToFile(right);
            writeToFile("\n");

            return result;
        }

        if(strcmp(startPoint->FuncName, "ls") == 0)
        {
            char* result = getVarProcessName();
            writeToFile(result);
            writeToFile(" = ");
            writeToFile("shl i32 ");
            writeToFile(left);
            writeToFile(",");
            writeToFile(right);
            writeToFile("\n");

            return result;
        }

        if(strcmp(startPoint->FuncName, "rs") == 0)
        {
            char* result = getVarProcessName();
            writeToFile(result);
            writeToFile(" = ");
            writeToFile("lshr i32 ");
            writeToFile(left);
            writeToFile(",");
            writeToFile(right);
            writeToFile("\n");

            return result;
        }

        if(strcmp(startPoint->FuncName, "lr") == 0)
        {
            char* result = getVarProcessName();
            writeToFile(result);
            writeToFile(" = ");
            writeToFile("fshl i32 ");
            writeToFile(left);
            writeToFile(",");
            writeToFile(right);
            writeToFile("\n");

            return result;
        }

        if(strcmp(startPoint->FuncName, "rr") == 0)
        {
            char* result = getVarProcessName();
            writeToFile(result);
            writeToFile(" = ");
            writeToFile("fshr i32 ");
            writeToFile(left);
            writeToFile(",");
            writeToFile(right);
            writeToFile("\n");

            return result;
        }

        return "error";
    }

    if (startPoint->Type == OneParameterFunction)
    {
        //long long child = calculate(startPoint->SingleChild);


        return "to be continued";
    }

    if(startPoint->Type == Number)
    {
        return startPoint->Number;
    }

    if(startPoint->Type == Variable)
    {
        char* result = getVarProcessName();
        writeToFile(result);
        writeToFile(" = ");
        writeToFile("load i32, i32*");
        writeToFile(" %");
        writeToFile(startPoint->VariableName);

        return result;

    }

}