// Include guard to prevent multiple inclusions of this header file -> only one instance of the header file is included in the program
#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "stack.h" // Include stack.h for Stack type

// Function to check if a character is an operator
int isOperator(char ch);

// Function to get the precedence of an operator
int precedence(char op);

// Function to check if the operator is right associative
int isRightAssociative(char op);

// Function to handle operands in the infix expression
void handleOperand(char *infix, char *postfix, int *i, int *j);

// Function to handle operators in the infix expression
void handleOperator(Stack *ops, Stack *values, char op);

// Function to evaluate an infix expression
double evaluateInfix(char *infix);

#endif // CALCULATOR_H