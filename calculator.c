#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "calculator.h"
#include "complex_operations.h" // Include complex_operations.h
#include "config.h"

// Get the precedence of the operator
int precedence(char op)
{
    switch (op)
    {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        case 's': // Square root
        case 'l': // Logarithm
        case 'S': // Sine
        case 'C': // Cosine
        case 'T': // Tangent
        case 'e': // Exponential
            return 4;
        default:
            return 0;
    }
}

// Check if the character is an operator
// Remove the definition of isOperator

// Check if the operator is right associative
int isRightAssociative(char op)
{
    return op == '^';
}

// Handle operands in the infix expression
void handleOperand(const char* infix, char* postfix, int* i, int* j)
{
    while (isdigit(infix[*i]) || infix[*i] == '.' || infix[*i] == 'i')
    {
        postfix[(*j)++] = infix[(*i)++];
    }
    postfix[(*j)++] = ' '; // Add space to separate operands
}

// Handle operators in the infix expression
void handleOperator(Stack* s, char* postfix, int* j, char op)
{
    Complex topOp;
    while (!isEmpty(s) && (peek(s, &topOp) == 0) && (precedence((char)topOp.real) > precedence(op) ||
        (precedence((char)topOp.real) == precedence(op) && !isRightAssociative(op))))
    {
        pop(s, &topOp);
        postfix[(*j)++] = (char)topOp.real;
        postfix[(*j)++] = ' ';
    }
    Complex opComplex = { .real = (double)op, .imag = 0.0 };
    push(s, opComplex);
}

// Convert the infix expression to postfix expression using the shunting-yard algorithm
int infixToPostfix(const char* infix, char* postfix)
{
    Stack s;
    if (initStack(&s, MAX) != 0)
    {
        return -1;
    }
    int i = 0, j = 0;
    while (infix[i] != '\0')
    {
        if (isdigit(infix[i]) || infix[i] == '.' || infix[i] == 'i')
        {
            handleOperand(infix, postfix, &i, &j);
        }
        else if (infix[i] == '(')
        {
            Complex opComplex = { .real = (double)infix[i++], .imag = 0.0 };
            push(&s, opComplex); // Push the opening parenthesis to the stack
        }
        else if (infix[i] == ')')
        {
            Complex topOp;
            while (!isEmpty(&s) && (peek(&s, &topOp) == 0) && (char)topOp.real != '(')
            {
                pop(&s, &topOp);
                postfix[j++] = (char)topOp.real; // Pop operators from the stack and add them to the postfix expression until an opening parenthesis is found
                postfix[j++] = ' ';
            }
            pop(&s, &topOp); // Pop the opening parenthesis from the stack
            i++;
        }
        else if (isOperator(infix[i]))
        {
            if (infix[i] == '-' && (i == 0 || infix[i - 1] == '('))
            {
                postfix[j++] = '0';
                postfix[j++] = ' ';
            }
            handleOperator(&s, postfix, &j, infix[i++]);
        }
    }
    Complex topOp;
    while (!isEmpty(&s) && (peek(&s, &topOp) == 0))
    {
        pop(&s, &topOp);
        postfix[j++] = (char)topOp.real; // Pop the remaining operators from the stack and add them to the postfix expression
        postfix[j++] = ' ';
    }
    postfix[j - 1] = '\0'; // Null-terminate the postfix expression
    freeStack(&s);
    return 0;
}

#include "calculator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Function to evaluate the input expression
double evaluateExpression(const char* expression) {
    // Implement your expression evaluation logic here
    // For simplicity, let's assume it returns a fixed value
    return 5.0;
}

// Function to convert a double to binary string
void doubleToBinary(double num, char* binaryStr) {
    int intPart = (int)num;
    int i = 0;
    while (intPart > 0) {
        binaryStr[i++] = (intPart % 2) ? '1' : '0';
        intPart /= 2;
    }
    binaryStr[i] = '\0';
    // Reverse the string
    for (int j = 0; j < i / 2; ++j) {
        char temp = binaryStr[j];
        binaryStr[j] = binaryStr[i - j - 1];
        binaryStr[i - j - 1] = temp;
    }
}

// Function to convert a double to hexadecimal string
void doubleToHex(double num, char* hexStr) {
    sprintf(hexStr, "%X", (int)num);
}

// Function to display the results in the specified formats
void displayResults(double result, const char* formats) {
    char binaryStr[64];
    char hexStr[64];
    for (int i = 0; formats[i] != '\0'; ++i) {
        switch (formats[i]) {
            case 'd':
                printf("Decimal: %f\n", result);
                break;
            case 'b':
                doubleToBinary(result, binaryStr);
                printf("Binary: %s\n", binaryStr);
                break;
            case 'h':
                doubleToHex(result, hexStr);
                printf("Hexadecimal: %s\n", hexStr);
                break;
            default:
                printf("Unknown format: %c\n", formats[i]);
                break;
        }
    }
}