// Include guard to prevent multiple inclusions of this header file -> only one instance of the header file is included in the program
#ifndef CALCULATOR_H
#define CALCULATOR_H

// Function to convert infix expression ("1 + 2") to postfix expression ("1 2 +")
void infixToPostfix(char *infix, char *postfix);

// Function to evaluate a postfix expression
double evaluatePostfix(char *postfix);

// Function to check if a character is an operator
int isOperator(char ch);

// Function to get the precedence of an operator
// Higher precedence value means higher priority
int precedence(char op);

#endif // CALCULATOR_H