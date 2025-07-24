#ifndef EXPRESSION_CONVERSION_H
#define EXPRESSION_CONVERSION_H

#include "stack.h"

void infixToPostfix(char *infix, char *postfix);
double evaluatePostfix(char *postfix);

// Prototype for handlePostfixOperator
void handlePostfixOperator(Stack *s, char op);

#endif // EXPRESSION_CONVERSION_H
