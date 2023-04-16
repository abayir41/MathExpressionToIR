#ifndef PRJ1_LEXER_H
#define PRJ1_LEXER_H

#include "Structures.h"

//Generates lexemes
//outTokenArray will be filled with lexemes, it is a return variable from parameter
//outSize will be count of lexemes, it is a return variable from parameter
void GetLexemes(const char line[], Token outTokenArray[], int* outSize);

#endif //PRJ1_LEXER_H
