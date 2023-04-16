#ifndef PRJ1_STRUCTURES_H
#define PRJ1_STRUCTURES_H

//It will be used in Node struct that will give clues about what info Node carries.
typedef enum {
    BitAnd = 0,
    BitOr = 1,
    Plus = 2,
    Minus = 3,
    Comma = 4,
    Multiply = 5,
    Divide = 6,
    Variable = 7,
    LeftParenthesis = 8,
    RightParenthesis = 9,
    Number = 10,
    TwoParameterFunction = 11,
    OneParameterFunction = 12
} TokenType;

//It will help the creating Node struct instances.
typedef struct {
    TokenType type;
    char value[256];
} Token;

/* The node struct
 * The variables will be set according to TokenType
 * For example if token is number then just Number variable will be set
 * if token is TwoParameterFunciton then Right, Left and FuncName will be set
 * */
struct Node {
    TokenType Type;

    //binary node
    char FuncName[5];
    struct Node* Right;
    struct Node* Left;
    struct Node* SingleChild;

    //value
    char VariableName[256];
    char Number[256];
};

//It will keep the variable data and name.
struct VariableStruct{
    char variableName[256];
    long long value;
};

#endif //PRJ1_STRUCTURES_H