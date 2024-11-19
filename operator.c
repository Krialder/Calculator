#include "operator.h"
#include <math.h>
#include "common.h" // Include common.h for HANDLE_ERROR

int precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return 0;
    }
}

double applyOperation(double operand1, double operand2, char op) {
    switch (op) {
        case '+':
            return operand1 + operand2;
        case '-':
            return operand1 - operand2;
        case '*':
            return operand1 * operand2;
        case '/':
            if (operand2 == 0) {
                HANDLE_ERROR("Division by zero", 0);
                return NAN;
            }
            return operand1 / operand2;
        case '^':
            return pow(operand1, operand2);
        default:
            HANDLE_ERROR("Invalid operator", 0);
            return NAN;
    }
}

int isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
}

// Check if the operator is right associative
int isRightAssociative(char op) 
{
    return op == '^';
}
