#include "expression_conversion.h"
#include "stack.h"
#include "operator.h"
#include "operand.h"
#include "error.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define STACK_SIZE 100 // Define STACK_SIZE with an appropriate value

// Convert the infix expression to postfix expression using the shunting-yard algorithm
void infixToPostfix(char *infix, char *postfix) 
{
    Stack s;
    int j = 0;
    initStack(&s, STACK_SIZE);
    int i = 0;
    while (infix[i] != '\0') {
        // Skip spaces
        if (infix[i] == ' ') { i++; continue; }
        // If number (multi-digit)
        if (isdigit(infix[i]) || (infix[i] == '-' && isdigit(infix[i+1]))) {
            int k = i;
            while (infix[k] != '\0' && (isdigit(infix[k]) || infix[k] == '.' || (k == i && infix[k] == '-'))) k++;
            strncpy(postfix + j, infix + i, k - i);
            j += k - i;
            postfix[j++] = ' ';
            i = k;
            continue;
        }
        // If operator
        if (isOperator(infix[i])) {
            while (!isEmpty(&s) && isOperator(peek(&s)) &&
                   ((precedence(peek(&s)) > precedence(infix[i])) ||
                    (precedence(peek(&s)) == precedence(infix[i]) && !isRightAssociative(infix[i])))) {
                postfix[j++] = pop(&s);
                postfix[j++] = ' ';
            }
            push(&s, infix[i]);
            i++;
            continue;
        }
        // If left parenthesis
        if (infix[i] == '(') {
            push(&s, infix[i]);
            i++;
            continue;
        }
        // If right parenthesis
        if (infix[i] == ')') {
            while (!isEmpty(&s) && peek(&s) != '(') {
                postfix[j++] = pop(&s);
                postfix[j++] = ' ';
            }
            if (!isEmpty(&s) && peek(&s) == '(') {
                pop(&s);
            } else {
                handleError("Mismatched parentheses");
            }
            i++;
            continue;
        }
        // Invalid character
        handleError("Invalid character in infix expression");
    }
    // Pop remaining operators
    while (!isEmpty(&s)) {
        if (peek(&s) == '(' || peek(&s) == ')') {
            handleError("Mismatched parentheses");
        }
        postfix[j++] = pop(&s);
        postfix[j++] = ' ';
    }
    postfix[j] = '\0';
}

// Evaluate the postfix expression
double evaluatePostfix(char *postfix) 
{
    // ...existing code...
    Stack s;
    initStack(&s, STACK_SIZE);
    int i = 0;
    while (postfix[i] != '\0') 
    {
        if (isdigit(postfix[i]) || postfix[i] == '.' || (postfix[i] == '-' && (i == 0 || postfix[i - 1] == ' '))) {
            handlePostfixOperand(&s, postfix, &i);
            while (postfix[i] == ' ') i++;
        } 
        else if (isOperator(postfix[i])) 
        {
            if (isEmpty(&s)) 
            {
                handleError("Stack underflow before handling operator");
            }
            handlePostfixOperator(&s, postfix[i]);
            i++;
            while (postfix[i] == ' ') i++;
        } 
        else 
        {
            handleError("Invalid character in postfix expression");
        }
    }
    // ...existing code...
    if (isEmpty(&s)) 
    {
        handleError("Invalid postfix expression");
    }
    double result = pop(&s);
    if (!isEmpty(&s))
    {
        handleError("Invalid postfix expression");
    }
    // ...existing code...
    return result;
}

// Implementation of handlePostfixOperator
void handlePostfixOperator(Stack *s, char op)
{
    double b = pop(s);
    double a = pop(s);
    double result = applyOperation(a, b, op);
    push(s, result);
}
