#include "operand.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void handleOperand(char *infix, char *postfix, int *i, int *j) 
{
    // Copy a number (multi-digit, possibly with decimal) from infix to postfix
    int k = *i;
    while (infix[k] != '\0' && (isdigit(infix[k]) || infix[k] == '.' || (k == *i && infix[k] == '-'))) {
        postfix[*j] = infix[k];
        (*j)++;
        k++;
    }
    postfix[(*j)++] = ' ';
    *i = k;
}

// Handle operands in the postfix expression
void handlePostfixOperand(Stack *s, char *postfix, int *i) 
{
    // Parse a number (integer or float) from postfix starting at *i
    char buffer[32];
    int k = 0;
    // Skip leading spaces
    while (postfix[*i] == ' ') (*i)++;
    // Handle negative numbers
    if (postfix[*i] == '-') {
        buffer[k++] = postfix[(*i)++];
    }
    // Parse digits and decimal point
    while (isdigit(postfix[*i]) || postfix[*i] == '.') {
        buffer[k++] = postfix[(*i)++];
    }
    buffer[k] = '\0';
    if (k > 0) {
        double value = atof(buffer);
        push(s, value);
    }
    // Skip trailing spaces
    while (postfix[*i] == ' ') (*i)++;
}

// Handle operands in the stack
void handleStackOperand(Stack *s, char *operand) 
{
    // Parse and push a number from operand string
    double value = atof(operand);
    push(s, value);
}
