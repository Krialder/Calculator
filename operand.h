#ifndef OPERAND_H
#define OPERAND_H

#include "stack.h" // Include the header file where Stack is defined

void handleOperand(char *infix, char *postfix, int *i, int *j);
void handleStackOperand(Stack *s, char *operand);

#endif // OPERAND_H

