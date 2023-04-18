#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Structures.h"
#include "VariableController.h"

//Pretty straightforward calculate function. Take root of tree and calculate it recursively. When find any number or variable return their values.
long long calculate(const struct Node* startPoint){

    if (startPoint->Type == BitAnd)
    {
        long long left = calculate(startPoint->Left);
        long long right = calculate(startPoint->Right);

        return left & right;
    }

    if (startPoint->Type == BitOr)
    {
        long long left = calculate(startPoint->Left);
        long long right = calculate(startPoint->Right);

        return left | right;
    }

    if (startPoint->Type == Plus)
    {
        long long left = calculate(startPoint->Left);
        long long right = calculate(startPoint->Right);

        return left + right;
    }

    if (startPoint->Type == Minus)
    {
        long long left = calculate(startPoint->Left);
        long long right = calculate(startPoint->Right);

        return left - right;
    }

    if (startPoint->Type == Multiply)
    {
        long long left = calculate(startPoint->Left);
        long long right = calculate(startPoint->Right);

        return left * right;
    }

    if (startPoint->Type == Modulo)
    {
        long long left = calculate(startPoint->Left);
        long long right = calculate(startPoint->Right);

        return left % right;
    }

    if (startPoint->Type == Divide)
    {
        long long left = calculate(startPoint->Left);
        long long right = calculate(startPoint->Right);

        return left / right;
    }

    if (startPoint->Type == TwoParameterFunction)
    {
        long long left = calculate(startPoint->Left);
        long long right = calculate(startPoint->Right);

        if(strcmp(startPoint->FuncName, "xor") == 0)
        {
            return left ^ right;
        }

        if(strcmp(startPoint->FuncName, "ls") == 0)
        {
            return left << right;
        }

        if(strcmp(startPoint->FuncName, "rs") == 0)
        {
            return left >> right;
        }

        if(strcmp(startPoint->FuncName, "lr") == 0)
        {
            return (left << right) | (left >> (64 - right));
        }

        if(strcmp(startPoint->FuncName, "rr") == 0)
        {
            return (left >> right) | (left << (64 - right));
        }

        return -1;
    }

    if (startPoint->Type == OneParameterFunction)
    {
        long long child = calculate(startPoint->SingleChild);
        return ~child;
    }

    if(startPoint->Type == Number)
    {
        return strtoll(startPoint->Number, NULL,10);
    }

    if(startPoint->Type == Variable)
    {
        return getVariableValue(startPoint->VariableName);
    }

}