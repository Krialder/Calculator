// Include guard to prevent multiple inclusions of this header file -> only one instance of the header file is included in the program
#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "stack.h" // Include stack.h for Stack type

// Function to convert infix expression (e.g., "1 + 2") to postfix expression (e.g., "1 2 +")
void infixToPostfix(char *infix, char *postfix);

// Function to evaluate a postfix expression
double evaluatePostfix(char *postfix);

// Function to check if a character is an operator
int isOperator(char ch);

// Function to get the precedence of an operator
int precedence(char op);

// Function to check if the operator is right associative
int isRightAssociative(char op);

// Function to handle operands in the infix expression
void handleOperand(char *infix, char *postfix, int *i, int *j);

// Function to handle operators in the infix expression
void handleOperator(Stack *s, char *postfix, int *j, char op);

// Function to handle operands in the postfix expression
void handlePostfixOperand(Stack *s, char *postfix, int *i);

// Function to handle operators in the postfix expression
void handlePostfixOperator(Stack *s, char op);

// Function to evaluate an infix expression
double evaluateInfix(char *infix);

#endif // CALCULATOR_H