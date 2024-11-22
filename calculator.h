// Include guard to prevent multiple inclusions of this header file -> only one instance of the header file is included in the program
#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "config.h" // Include the configuration header file

typedef struct {
    double real;
    double imag;
} Complex;

// Function to convert infix expression (e.g., "1 + 2") to postfix expression (e.g., "1 2 +")
int infixToPostfix(const char* infix, char* postfix);

// Function to get the precedence of an operator
// Higher precedence value means higher priority
int precedence(char op);

// Declaration of isOperator function
int isOperator(char op);

typedef struct {
    Complex* items; // Pointer to dynamically allocated array to store stack elements
    int top;       // Index of the top element
    int capacity;  // Current capacity of the stack
} Stack;

int isRightAssociative(char op);
void handleOperand(const char* infix, char* postfix, int* i, int* j);
void handleOperator(Stack* s, char* postfix, int* j, char op);

// Function to evaluate the input expression
double evaluateExpression(const char* expression);

// Function to convert a double to binary string
void doubleToBinary(double num, char* binaryStr);

// Function to convert a double to hexadecimal string
void doubleToHex(double num, char* hexStr);

// Function to display the results in the specified formats
void displayResults(double result, const char* formats);

#endif // CALCULATOR_H