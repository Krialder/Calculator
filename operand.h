#ifndef OPERAND_H
#define OPERAND_H

void handleOperand(char *infix, char *postfix, int *i, int *j);
#include "stack.h" // Include the header file where Stack is defined

void handlePostfixOperand(Stack *s, char *postfix, int *i);

#endif // OPERAND_H
