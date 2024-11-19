#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>

// Common utility functions and macros can be declared here
extern int isValidCharacter(char ch);
void handleError(const char *message, const char *file, const int line, const int exitProgram);

#define HANDLE_ERROR(msg, exitProgram) handleError(msg, __FILE__, __LINE__, exitProgram)

#define STACK_UNDERFLOW -1
#define STACK_OVERFLOW -2

#endif // COMMON_H