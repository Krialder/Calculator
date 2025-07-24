#include "operator.h"
#include <math.h>
#include <stdio.h>

// Get the precedence of the operator
int precedence(char op) 
{
    switch (op) {
        case '+':
        case '-': return 1;
        case '*':
        case '/':
        case '%': return 2;
        case '^': return 3;
        default: return 0;
    }
}

// Check if the character is an operator
int isOperator(char ch) 
{
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^' || ch == '%';
}

// Check if the operator is right associative
int isRightAssociative(char op) 
{
    return op == '^';
}

// Apply the operation to two operands
double applyOperation(double a, double b, char op) 
{
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0) {
                printf("Error: Division by zero!\n");
                return 0;
            }
            return a / b;
        case '^': return pow(a, b);
        case '%':
            if (b == 0) {
                printf("Error: Modulo by zero!\n");
                return 0;
            }
            return fmod(a, b);
        default:
            printf("Error: Unknown operator '%c'!\n", op);
            return 0;
    }
}
