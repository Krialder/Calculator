#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#include "stack.h"
#include "calculator.h"
#include "conversion.h"
#include "operator.h"
#include "operand.h"
#include "expression_conversion.h"
#include "common.h"

// Function declarations
void handleOperand(char *infix, char *postfix, int *i, int *j);
void handleStackOperand(Stack *s, char *operand);
void infixToPostfix(char *infix, char *postfix);
double evaluatePostfix(const char *postfix);
void handlePostfixOperator(Stack *s, char operator);
void handleInfixOperand(char *infix, char *postfix, int *i, int *j);
void handleInfixParenthesis(Stack *s, char *postfix, int *j);
void handleInfixOperator(Stack *s, char *postfix, int *j, char operator);
void handlePostfixToken(const char *expression, char *token, int *i, int *j);
extern void handlePostfixOperand(const char *token, double *stack, int *top);

// Additional function declarations
void initializeStack(Stack *s);
int isOperator(char c);
int precedence(char operator);
double performOperation(double operand1, double operand2, char operator);
int isBinary(const char *input);
int isDecimal(const char *input);
int isHexadecimal(const char *input);
int isNegativeBinary(const char *input);
int isNegativeHexadecimal(const char *input);
int isNegativeDecimal(const char *input);
int isOctal(const char *input);
int isNegativeOctal(const char *input);
int convertNegativeBinaryToDecimal(const char *input);
int convertNegativeHexadecimalToDecimal(const char *input);
int convertNegativeDecimalToDecimal(const char *input);
int convertNegativeOctalToDecimal(const char *input);
int octalToDecimal(const char *octal);
double applyOperation(double val1, double val2, char op);
int push(Stack *s, double value); // Changed return type to int
int pop(Stack *s, double *value); // Changed return type to int and added double* parameter

// Additional function declarations for complete functionality
void convertToBinary(int decimal, char *binary);
void convertToHexadecimal(int decimal, char *hexadecimal);
void convertToOctal(int decimal, char *octal);
int binaryToDecimal(const char *binary);
int hexadecimalToDecimal(const char *hexadecimal);
int decimalToDecimal(const char *decimal);
int octalToDecimal(const char *octal);
void decimalToNegativeBinary(int decimal, char *binary);
void decimalToNegativeHexadecimal(int decimal, char *hex);
extern void handleParentheses(Stack *ops, Stack *values);

#endif // DECLARATIONS_H