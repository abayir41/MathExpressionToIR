#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "Structures.h"
#include "Lexer.h"
#include "Parser.h"
#include "VariableController.h"
#include "Calculator.h"

long long proccesTheExpression(const char expression[]);
bool splitFromAssignSign(const char line[], char outVariablePart[], char outExpression[]);

FILE *outputFilePtr;
int main(int argc, char *argv[]) {

    char* filenameOriginal = "D:\\da.txt";
    char fileNameCopy[strlen(filenameOriginal)];
    char fileNameCopy2[strlen(filenameOriginal)];

    strcpy(fileNameCopy, filenameOriginal);
    strcpy(fileNameCopy2, filenameOriginal);


    char* dot = strrchr(fileNameCopy, '.');
    if(dot)
        *dot = '\0';

    int newFileNameLength = strlen(fileNameCopy) + 3;
    char newFileName[newFileNameLength];
    strcat(newFileName, fileNameCopy);
    strcat(newFileName, ".ll");
    newFileName[newFileNameLength] = '\0';



    outputFilePtr = fopen(newFileName, "w");

    fprintf(outputFilePtr, "; ModuleID = 'advcalc2ir'");
    fprintf(outputFilePtr, "\n");
    fprintf(outputFilePtr, "declare i32 @printf(i8*, ...)");
    fprintf(outputFilePtr, "\n");
    fprintf(outputFilePtr, "@print.str = constant [4 x i8] c\"%%d\\0A\\00\"");
    fprintf(outputFilePtr, "\n");
    fprintf(outputFilePtr, "define i32 @main() {");
    fprintf(outputFilePtr, "\n");


    FILE* inputFilePtr;
    inputFilePtr = fopen(fileNameCopy2, "r");
    if (inputFilePtr == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    char line[256 +1] = "";


    //program lifecycle
    while (fgets(line, sizeof(line), inputFilePtr)) {

        //ctrl+d cacth
        if(line == NULL){
            break;
        }

        //fgets comes with new line, removing it to run code properly
        line[strcspn(line, "\n")] = 0;

        //if there is not a '='
        if(strchr(line, '=') == NULL)
        {
            long long value = proccesTheExpression(line);

            //check
            if(anyErrorOccurred())
            {
                printf("Error!");
                printf("\n");
                printf("> ");
                continue;
            }

            printf("%lld", value);
            printf("\n");
            printf("> ");
        }
        else
        {
            char variablePart[257];
            char expression[257];

            //Split from equal sign, if there is a error it will return false
            if(!splitFromAssignSign(line, variablePart, expression))
            {
                printf("Error!");
                printf("\n");
                printf("> ");
                continue;
            }

            long long value = proccesTheExpression(expression);

            //check
            if(anyErrorOccurred())
            {
                printf("Error!");
                printf("\n");
                printf("> ");
                continue;
            }

            //setting variable
            setVariableValue(variablePart, value);
            printf("> ");
        }
    }

    disposeVariables();
    fprintf(outputFilePtr, "}");

    fclose(inputFilePtr);
    fclose(outputFilePtr);

    return 0;
}

long long proccesTheExpression(const char expression[])
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
    long long result = calculate(root);

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
void writeToFile(char line[] ){
    fprintf(outputFilePtr, line);
}