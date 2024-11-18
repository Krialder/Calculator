#include "expression_conversion.h"
#include "stack.h"
#include "operator.h"
#include "operand.h"
#include "error.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_SIZE 100 // Define STACK_SIZE with an appropriate value

// Convert the infix expression to postfix expression using the shunting-yard algorithm
void infixToPostfix(char *infix, char *postfix) 
{
    // ...existing code...
    Stack s;
    int j = 0;
    initStack(&s, STACK_SIZE); // Assuming STACK_SIZE is defined appropriately
    while (!isEmpty(&s)) {
        if (peek(&s) == '(') {
            handleError("Mismatched parentheses");
        }
        postfix[j++] = pop(&s);
        postfix[j++] = ' ';
    }
    // ...existing code...
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
