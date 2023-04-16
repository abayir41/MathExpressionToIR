#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Structures.h"

int position;
int tokenCount;
const Token* tokenPtr;
bool errorOccurred;

bool anyErrorOccurred () {
    if(position != tokenCount) return true;
    return errorOccurred;
}

//make ready the parser system
void PrepareParser(int TokenCount, const Token* TokenPtr)
{
    position = 0;
    tokenCount = TokenCount;
    tokenPtr = TokenPtr;
    errorOccurred = false;
}

//recursively dispose node pointer
void DisposeParser(struct Node* startPoint)
{
    if (startPoint == NULL) return;

    if  (startPoint->Type == BitOr |
         startPoint->Type == BitAnd |
         startPoint->Type == Plus |
         startPoint->Type == Minus |
         startPoint->Type == Multiply |
         startPoint->Type == Divide |
         startPoint->Type == TwoParameterFunction)
    {
        DisposeParser(startPoint->Left);
        DisposeParser(startPoint->Right);
    }

    if  (startPoint->Type == OneParameterFunction)
    {
        DisposeParser(startPoint->SingleChild);
    }

    free(startPoint);
}

/*
recursive descent parser algorithm
The BNF grammer for this algorithm

<bitor> ::= <bitor> | <bitor> "|" <bitor>
<bitand> ::= <sum> | <bitand> "&" <sum>
<sum> ::= <fac> | <sum> "+" <fac> | <sum> "-" <fac>
<fac> ::= <par> | <fac> "*" <par> | <fac> "/" <par>
<par> ::= <func> | "(" <bitor> ")"
<func> ::= <number> | <var> | <funcname> "(" <bitor> "," <bitor> ")" | <funcname> "(" <bitor> ")"
<number> ::= <digit> | <digit> <number>
<digit> ::= [0-9]
<var> ::= <alpha> | <alpha> <var>
<alpha> ::= [a-z] | [A-Z]
<funcname> ::= "xor" | "ls" | "rs" | "lr" | "rr" | "not"
*/

struct Node* ParseBitAnd();
struct Node* ParseBitOr();
struct Node* ParseSum();
struct Node* ParseFac();
struct Node* ParseParentheses();
struct Node* ParseFunc();

struct Node* ParseBitOr() {
    struct Node* left = ParseBitAnd();
    while (position < tokenCount && tokenPtr[position].type == BitOr) {
        position++;

        struct Node* right = ParseBitAnd();

        struct Node* newLeft = (struct Node*) malloc(sizeof(struct Node));
        newLeft->Type = BitOr;
        newLeft->Left = left;
        newLeft->Right = right;
        left = newLeft;
    }
    return left;
}

struct Node* ParseBitAnd(){
    struct Node* left = ParseSum();
    while (position < tokenCount && tokenPtr[position].type == BitAnd) {
        position++;

        struct Node* right = ParseSum();

        struct Node* newLeft = (struct Node*) malloc(sizeof(struct Node));
        newLeft->Type = BitAnd;
        newLeft->Left = left;
        newLeft->Right = right;

        left = newLeft;
    }

    return left;
}

struct Node* ParseSum() {
    struct Node* left = ParseFac();
    while (position < tokenCount && (tokenPtr[position].type == Plus || tokenPtr[position].type == Minus)) {
        Token op = tokenPtr[position];
        position++;
        struct Node* right = ParseFac();

        struct Node* newLeft = (struct Node*) malloc(sizeof(struct Node));
        newLeft->Type = op.type;
        newLeft->Left = left;
        newLeft->Right = right;
        left = newLeft;
    }
    return left;
}

struct Node* ParseFac() {
    struct Node* left = ParseParentheses();
    while (position < tokenCount && (tokenPtr[position].type == Divide || tokenPtr[position].type == Multiply)) {
        Token op = tokenPtr[position];
        position++;

        struct Node* right = ParseParentheses();
        struct Node* newLeft = (struct Node*) malloc(sizeof(struct Node));
        newLeft->Type = op.type;
        newLeft->Left = left;
        newLeft->Right = right;
        left = newLeft;
    }
    return left;
}

struct Node* ParseParentheses()
{

    if (tokenPtr[position].type == LeftParenthesis)
    {
        position++;
        struct Node* node = ParseBitOr();
        if (tokenPtr[position].type != RightParenthesis)
        {
            errorOccurred = true;
            return NULL;
        }

        position++;
        return node;
    }

    return ParseFunc();
}

struct Node* ParseFunc()
{
    if (tokenPtr[position].type == Number)
    {
        struct Node* numberNode = (struct Node*) malloc(sizeof(struct Node));

        numberNode->Type = Number;
        strcpy(numberNode->Number, tokenPtr[position].value);

        position++;

        return numberNode;
    }

    if (tokenPtr[position].type == Variable)
    {
        struct Node* variableNode = (struct Node*) malloc(sizeof(struct Node));
        variableNode->Type = Variable;
        strcpy(variableNode->VariableName, tokenPtr[position].value);

        position++;

        return variableNode;
    }

    if (tokenPtr[position].type == TwoParameterFunction)
    {
        Token func = tokenPtr[position];
        position++;
        if (tokenPtr[position].type != LeftParenthesis)
        {
            errorOccurred = true;
            return NULL;
        }

        position++;
        struct Node* left = ParseBitOr();

        if(tokenPtr[position].type != Comma)
        {
            errorOccurred = true;
            return NULL;
        }

        position++;
        struct Node* right = ParseBitOr();


        if(tokenPtr[position].type != RightParenthesis)
        {
            errorOccurred = true;
            return NULL;
        }
        position++;

        struct Node* newFuncNode = (struct Node*) malloc(sizeof(struct Node));
        newFuncNode->Type = TwoParameterFunction;
        strcpy(newFuncNode->FuncName, func.value);
        newFuncNode->Left = left;
        newFuncNode->Right = right;

        return newFuncNode;
    }

    if (tokenPtr[position].type == OneParameterFunction)
    {
        Token func = tokenPtr[position];
        position++;
        if (tokenPtr[position].type != LeftParenthesis)
        {
            errorOccurred = true;
            return NULL;
        }

        position++;
        struct Node* child = ParseBitOr();


        if(tokenPtr[position].type != RightParenthesis)
        {
            errorOccurred = true;
            return NULL;
        }

        position++;

        struct Node* newFuncNode = (struct Node*) malloc(sizeof(struct Node));
        newFuncNode->Type = OneParameterFunction;
        strcpy(newFuncNode->FuncName, func.value);
        newFuncNode->SingleChild = child;

        return newFuncNode;
    }


    errorOccurred = true;
    return NULL;

}
