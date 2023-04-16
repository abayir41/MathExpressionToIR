#ifndef PRJ1_VARIABLECONTROLLER_H
#define PRJ1_VARIABLECONTROLLER_H

//Sets variable
void setVariableValue(const char* name, long long value);

//Gets variable
long long getVariableValue(const char* name);

//Disposed Saved Variables
void disposeVariables();

#endif //PRJ1_VARIABLECONTROLLER_H
