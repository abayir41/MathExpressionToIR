cmake_minimum_required(VERSION 3.24)
project(prj1 C)

set(CMAKE_C_STANDARD 11)

add_executable(prj1 main.c Lexer.c Parser.c VariableController.c Calculator.c Calculator.h Lexer.h Parser.h VariableController.h Structures.h ProcessCounter.h ProccesCounter.c)
