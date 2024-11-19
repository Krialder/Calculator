#include "common.h"
#include "operator.h" // Include operator.h for isOperator
#include <ctype.h> // Include ctype.h for isdigit and isspace
// ...existing code...

int isValidCharacter(char ch) {
    return isdigit(ch) || ch == '.' || ch == '(' || ch == ')' || isOperator(ch) || isspace(ch) || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
}

void handleError(const char *message, const char *file, const int line, const int exitProgram) {
    fprintf(stderr, "Error: %s in file %s at line %d\n", message, file, line);
    if (exitProgram) {
        exit(EXIT_FAILURE);
    }
}