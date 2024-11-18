#include "operator.h"
#include <math.h>

// Get the precedence of the operator
int precedence(char op) 
{
    // ...existing code...
}

// Check if the character is an operator
int isOperator(char ch) 
{
    // ...existing code...
}

// Check if the operator is right associative
int isRightAssociative(char op) 
{
    // ...existing code...
}

// Apply the operation to two operands
double applyOperation(double a, double b, char op) 
{
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        case '^': return pow(a, b);
        case '%': return fmod(a, b);
        // ...additional cases for other operators...
        default: return 0;
    }
}
