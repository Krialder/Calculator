#include "operand.h"
#include "stack.h" // Include stack.h for Stack type
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "declarations.h" // Include declarations.h

// Handle operands in the infix expression
void handleOperand(char *infix, char *postfix, int *i, int *j) 
{
    int isNegative = 0;
    if (infix[*i] == '-') {
        isNegative = 1;
        postfix[*j] = infix[*i];
        (*j)++;
        (*i)++;
    }
    char operand[20];
    int k = 0;
    while (isdigit(infix[*i]) || infix[*i] == '.' || isxdigit(infix[*i])) {
        operand[k++] = infix[*i];
        (*i)++;
    }
    operand[k] = '\0';
    double value;
    if (isBinary(operand)) {
        value = binaryToDecimal(operand);
    } else if (isHexadecimal(operand)) {
        value = hexadecimalToDecimal(operand);
    } else {
        value = atof(operand);
    }
    if (isNegative) {
        value = -value;
    }
    snprintf(postfix + *j, 20, "%lf ", value);
    *j += strlen(postfix + *j);
    (*i)--;
}

// Handle operands in the stack
void handleStackOperand(Stack *s, char *operand) 
{
    double value = atof(operand);
    if (push(s, value) == STACK_OVERFLOW) {
        HANDLE_ERROR("Stack overflow", 0);
    }
}
