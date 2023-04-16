#ifndef PRJ1_PARSER_H
#define PRJ1_PARSER_H

#include <stdbool.h>
#include "Structures.h"

//Before Parse system should be prepared
void PrepareParser(int TokenCount,const Token* TokenPtr);

//free the tree
void DisposeParser(struct Node* startPoint);

bool anyErrorOccurred ();
struct Node* ParseBitOr();

#endif //PRJ1_PARSER_H
