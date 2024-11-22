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
int isOperator(char ch)
{
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^' || ch == 's' || ch == 'l' || ch == 'S' || ch == 'C' || ch == 'T' || ch == 'e';
}

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