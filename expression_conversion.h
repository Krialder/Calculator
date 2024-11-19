#ifndef EXPRESSION_CONVERSION_H
#define EXPRESSION_CONVERSION_H

#include "stack.h"

void infixToPostfix(char *infix, char *postfix);
double evaluatePostfix(const char *postfix);
void handlePostfixOperator(Stack *s, char operator);
void handleInfixOperand(char *infix, char *postfix, int *i, int *j);
void handleInfixParenthesis(Stack *s, char *postfix, int *j);
void handleInfixOperator(Stack *s, char *postfix, int *j, char operator);
void handlePostfixToken(const char *expression, char *token, int *i, int *j);
int isValidCharacter(char ch);

#endif // EXPRESSION_CONVERSION_H
