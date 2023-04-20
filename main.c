#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "Structures.h"
#include "Lexer.h"
#include "Parser.h"
#include "VariableController.h"
#include "Calculator.h"
#include "ProcessCounter.h"

char* proccesTheExpression(const char expression[]);

bool splitFromAssignSign(const char line[], char outVariablePart[], char outExpression[]);

void fetchFileNameWithoutExtension(char* dest, const char* source);

void createNewFileName(char* dest, const char* source);

//File that our output
FILE *outputFilePtr;

int main(int argc, char *argv[]) {

    char* filenameOriginal = argv[1];

    //If there is a extension it will be removed. Ex: file.txt -> file
    char fileNameWithoutExtension[strlen(filenameOriginal) + 10];
    fileNameWithoutExtension[0] = '\0';
    fetchFileNameWithoutExtension(fileNameWithoutExtension, filenameOriginal);

    //.ll extension added. Ex: file -> file.ll
    char newFileName[strlen(fileNameWithoutExtension) + 10];
    newFileName[0] = '\0';
    createNewFileName(newFileName, fileNameWithoutExtension);

    outputFilePtr = fopen(newFileName, "w");

    fprintf(outputFilePtr, "; ModuleID = 'advcalc2ir'");
    fprintf(outputFilePtr, "\n");
    fprintf(outputFilePtr, "declare i32 @printf(i8*, ...)");
    fprintf(outputFilePtr, "\n");
    fprintf(outputFilePtr, "@print.str = constant [4 x i8] c\"%%d\\0A\\00\"");
    fprintf(outputFilePtr, "\n");
    fprintf(outputFilePtr, "\n");
    fprintf(outputFilePtr, "define i32 @main() {");
    fprintf(outputFilePtr, "\n");

    FILE* inputFilePtr;
    inputFilePtr = fopen(filenameOriginal, "r");
    if (inputFilePtr == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    char line[256 +1] = "";
    int currentLineNumberCounter = 1;

    //program lifecycle
    while (fgets(line, sizeof(line), inputFilePtr)) {

        if(line == NULL){
            break;
        }

        //fgets comes with new line, removing it to run code properly
        line[strcspn(line, "\n")] = 0;

        //if there is not a '='
        if(strchr(line, '=') == NULL)
        {
            char* value = proccesTheExpression(line);

            //check if parse tree worked without error
            if(anyErrorOccurred())
            {
                printf("Error on line %d!", currentLineNumberCounter);
                printf("\n");
                break;
            }

            //"=" is a error sign from calculator
            if(value[0] == '=')
            {
                printf("Error on line %d!", currentLineNumberCounter);
                printf("\n");
                break;
            }

            fprintf(outputFilePtr,"call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @print.str, i32 0, i32 0), i32 ");
            fprintf(outputFilePtr, "%s", value);
            fprintf(outputFilePtr, " )");
            fprintf(outputFilePtr, "\n");
            getProcessCount();

            free(value);
        }
        else
        {
            char variablePart[257];
            char expression[257];

            //Split from equal sign, if there is a error it will return false
            if(!splitFromAssignSign(line, variablePart, expression))
            {
                printf("Error on line %d!", currentLineNumberCounter);
                continue;
            }

            char* value = proccesTheExpression(expression);

            //check if parse tree worked without error
            if(anyErrorOccurred())
            {
                printf("Error on line %d!", currentLineNumberCounter);
                continue;
            }

            //"=" is a error sign from calculator
            if(value[0] == '=')
            {
                printf("Error on line %d!", currentLineNumberCounter);
                printf("\n");
                break;
            }

            //setting variable
            setVariableValue(variablePart, value);
        }

        currentLineNumberCounter++;
    }

    disposeVariables();
    fprintf(outputFilePtr, "ret i32 0\n");
    fprintf(outputFilePtr, "}");

    fclose(inputFilePtr);
    fclose(outputFilePtr);


    return 0;
}

char* proccesTheExpression(const char expression[])
{
    //creating lexemes
    Token tokens[256];
    int size = 0;
    GetLexemes(expression, tokens, &size);

    //creating parse tree
    PrepareParser(size,tokens);
    struct Node* root = ParseBitOr();

    //check if any error occured while parsing
    if(anyErrorOccurred())
    {
        DisposeParser(root);
        return 0;
    }

    //calculate parse tree
    char* result = calculate(root);

    //remove mallocs
    DisposeParser(root);

    return result;
}

bool splitFromAssignSign(const char line[], char outVariablePart[], char outExpression[])
{
    int pos = 0;
    //skipping start empty spaces
    while (line[pos] == ' ')
        pos++;

    int creator = 0;
    //fetching variable name
    while (isalpha(line[pos]))
    {
        outVariablePart[creator] = line[pos];
        pos++;
        creator++;
    }
    outVariablePart[creator] = '\0';

    //skipping after variable empty spaces
    while (line[pos] == ' ')
        pos++;

    //we should be at = sign, if not return false to throw error
    if(line[pos] != '=')
    {
        return false;
    }
    pos++;

    creator = 0;
    //fecth expression
    while (line[pos] != '\0')
    {
        outExpression[creator] = line[pos];
        creator++;
        pos++;
    }
    outExpression[creator] = '\0';

    return true;
}

void writeToFile(const char line[] )
{
    fprintf(outputFilePtr,"%s", line);
}

void fetchFileNameWithoutExtension(char* dest, const char* source)
{
    strcpy(dest, source);

    char* dot = strrchr(dest, '.');
    if(dot)
        *dot = '\0';
}

void createNewFileName(char* dest, const char* source)
{
    strcat(dest, source);
    strcat(dest, ".ll");
    dest[strlen(dest)] = '\0';
}
