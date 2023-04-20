#ifndef PRJ1_VARIABLECONTROLLER_H
#define PRJ1_VARIABLECONTROLLER_H
#include <stdbool.h>

//Sets variable
void setVariableValue(const char* name, const char* value);

//Checks if variable created
bool checkIfVariableExist(const char* name);

//Disposed Saved Variables
void disposeVariables();

#endif //PRJ1_VARIABLECONTROLLER_H
