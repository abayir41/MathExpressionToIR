#include <string.h>
#include <ctype.h>
#include "Structures.h"


//Generates lexemes
//outTokenArray will be filled with lexemes, it is a return variable from parameter
//outSize will be count of lexemes, it is a return variable from parameter
void GetLexemes(const char line[], Token outTokenArray[], int* outSize){
    int position = 0;
    *outSize = 0;

    while (line[position] != '\0')
    {
        char currentChar = line[position];

        if(currentChar == ' ')
        {
            position++;
            continue;
        }

        if(currentChar == '(')
        {
            outTokenArray[*outSize].type = LeftParenthesis;
            outTokenArray[*outSize].value[0] = '(';
            outTokenArray[*outSize].value[1] = '\0';
            position++;
            *outSize += 1;
            continue;
        }

        if(currentChar == ')')
        {
            outTokenArray[*outSize].type = RightParenthesis;
            outTokenArray[*outSize].value[0] = ')';
            outTokenArray[*outSize].value[1] = '\0';
            position++;
            *outSize += 1;
            continue;
        }

        if(currentChar == '+')
        {
            outTokenArray[*outSize].type = Plus;
            outTokenArray[*outSize].value[0] = '+';
            outTokenArray[*outSize].value[1] = '\0';
            position++;
            *outSize += 1;
            continue;
        }

        if(currentChar == '%')
        {
            outTokenArray[*outSize].type = Modulo;
            outTokenArray[*outSize].value[0] = '%';
            outTokenArray[*outSize].value[1] = '\0';
            position++;
            *outSize += 1;
            continue;
        }

        if(currentChar == '-')
        {
            outTokenArray[*outSize].type = Minus;
            outTokenArray[*outSize].value[0] = '-';
            outTokenArray[*outSize].value[1] = '\0';
            position++;
            *outSize += 1;
            continue;
        }

        if(currentChar == '*')
        {
            outTokenArray[*outSize].type = Multiply;
            outTokenArray[*outSize].value[0] = '*';
            outTokenArray[*outSize].value[1] = '\0';
            position++;
            *outSize += 1;
            continue;
        }

        if(currentChar == '/')
        {
            outTokenArray[*outSize].type = Divide;
            outTokenArray[*outSize].value[0] = '/';
            outTokenArray[*outSize].value[1] = '\0';
            position++;
            *outSize += 1;
            continue;
        }

        if(currentChar == '&')
        {
            outTokenArray[*outSize].type = BitAnd;
            outTokenArray[*outSize].value[0] = '&';
            outTokenArray[*outSize].value[1] = '\0';
            position++;
            *outSize += 1;
            continue;
        }

        if(currentChar == '|')
        {
            outTokenArray[*outSize].type = BitOr;
            outTokenArray[*outSize].value[0] = '|';
            outTokenArray[*outSize].value[1] = '\0';
            position++;
            *outSize += 1;
            continue;
        }

        if(currentChar == ',')
        {
            outTokenArray[*outSize].type = Comma;
            outTokenArray[*outSize].value[0] = ',';
            outTokenArray[*outSize].value[1] = '\0';
            position++;
            *outSize += 1;
            continue;
        }

        if (isdigit(line[position]))
        {
            int endOfNum = 0;
            outTokenArray[*outSize].type = Number;
            //check if it is end of the string
            while (isdigit(line[position])) {
                outTokenArray[*outSize].value[endOfNum] = line[position];
                endOfNum++;
                position++;
            }
            outTokenArray[*outSize].value[endOfNum] = '\0';
            *outSize += 1;
            continue;
        }

        //Catching string lexeme
        if (isalpha(line[position]))
        {
            int endOfString = 0;
            //check if it is end of the string
            while (isalpha(line[position])) {
                outTokenArray[*outSize].value[endOfString] = line[position];
                endOfString++;
                position++;
            }
            outTokenArray[*outSize].value[endOfString] = '\0';

            //Check if lexeme is a function
            if(strcmp(outTokenArray[*outSize].value,"xor") == 0 ||
               strcmp(outTokenArray[*outSize].value,"ls") == 0 ||
               strcmp(outTokenArray[*outSize].value,"lr") == 0 ||
               strcmp(outTokenArray[*outSize].value,"rs") == 0 ||
               strcmp(outTokenArray[*outSize].value,"rr") == 0)
            {
                outTokenArray[*outSize].type = TwoParameterFunction;
                *outSize += 1;
                continue;
            }

            //Check if lexeme is a function
            if(strcmp(outTokenArray[*outSize].value,"not") == 0)
            {
                outTokenArray[*outSize].type = OneParameterFunction;
                *outSize += 1;
                continue;
            }

            outTokenArray[*outSize].type = Variable;
            *outSize += 1;
            continue;
        }
    }
}