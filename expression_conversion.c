#include "expression_conversion.h"
#include "operator.h"
#include "operand.h"
#include "conversion.h" // Include conversion.h for handlePostfixOperand
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h> // Include math.h for pow function
#include "common.h" // Include common.h
#include "declarations.h" // Include declarations.h

#define STACK_SIZE 100

void handlePostfixOperator(Stack *s, char operator) {
    double operand2, operand1;
    if (s->top < 1) { // Ensure the stack has at least two operands
        HANDLE_ERROR("Invalid postfix expression", 0);
        return;
    }
    if (pop(s, &operand2) == STACK_UNDERFLOW || pop(s, &operand1) == STACK_UNDERFLOW) {
        HANDLE_ERROR("Invalid postfix expression", 0);
        return;
    }
    if (push(s, applyOperation(operand1, operand2, operator)) == STACK_OVERFLOW) {
        HANDLE_ERROR("Stack overflow", 0);
    }
}

void handlePostfixToken(const char *expression, char *token, int *i, int *j) {
    *j = 0;
    while (isdigit(expression[*i]) || expression[*i] == '.' || (expression[*i] == '-' && *j == 0)) {
        token[(*j)++] = expression[*i];
        (*i)++;
    }
    token[*j] = '\0';
}

double evaluatePostfix(const char *expression) {
    Stack stack;
    initStack(&stack, STACK_SIZE);
    char token[20];
    int i = 0, j = 0;

    while (expression[i] != '\0') {
        if (!isValidCharacter(expression[i])) {
            HANDLE_ERROR("Invalid character in postfix expression", 0);
            freeStack(&stack);
            return 0;
        }
        if (isspace(expression[i])) {
            i++;
            continue;
        }

        if (isdigit(expression[i]) || (expression[i] == '-' && isdigit(expression[i + 1])) || expression[i] == '.' || isxdigit(expression[i])) {
            handlePostfixToken(expression, token, &i, &j);
            handlePostfixOperand(token, stack.data, &stack.top);
        } else if (isOperator(expression[i])) {
            if (stack.top < 1) {
                HANDLE_ERROR("Invalid postfix expression: not enough operands", 0);
                freeStack(&stack);
                return 0;
            }
            double operand2 = stack.data[stack.top--];
            double operand1 = stack.data[stack.top--];
            if (push(&stack, applyOperation(operand1, operand2, expression[i])) == STACK_OVERFLOW) {
                HANDLE_ERROR("Stack overflow", 0);
                freeStack(&stack);
                return 0;
            }
            i++;
        } else {
            HANDLE_ERROR("Invalid character in postfix expression", 0);
            freeStack(&stack);
            return 0;
        }
    }
    if (stack.top != 0) {
        HANDLE_ERROR("Invalid postfix expression: not enough operands", 0);
        freeStack(&stack);
        return 0;
    }
    double result = stack.data[stack.top];
    freeStack(&stack);
    return result;
}

void infixToPostfix(char *infix, char *postfix) {
    Stack s;
    int j = 0;
    initStack(&s, STACK_SIZE);
    for (int i = 0; infix[i] != '\0'; i++) {
        if (!isValidCharacter(infix[i])) {
            HANDLE_ERROR("Invalid character in infix expression", 0);
            freeStack(&s);
            return;
        }
        if (isdigit(infix[i]) || infix[i] == '.' || isxdigit(infix[i])) {
            handleInfixOperand(infix, postfix, &i, &j);
        } else if (infix[i] == '(') {
            if (push(&s, infix[i]) == STACK_OVERFLOW) {
                HANDLE_ERROR("Stack overflow", 0);
                freeStack(&s);
                return;
            }
        } else if (infix[i] == ')') {
            handleInfixParenthesis(&s, postfix, &j);
        } else if (isOperator(infix[i])) {
            handleInfixOperator(&s, postfix, &j, infix[i]);
        }
    }
    while (!isEmpty(&s)) {
        if (peek(&s) == '(') {
            HANDLE_ERROR("Mismatched parentheses", 0);
            freeStack(&s);
            return;
        }
        double value;
        if (pop(&s, &value) == STACK_UNDERFLOW) {
            HANDLE_ERROR("Stack underflow", 0);
            freeStack(&s);
            return;
        }
        postfix[j++] = (char)value;
        postfix[j++] = ' ';
    }
    postfix[j] = '\0';
    freeStack(&s);
}

void handleInfixOperand(char *infix, char *postfix, int *i, int *j) {
    while (isdigit(infix[*i]) || infix[*i] == '.') {
        postfix[(*j)++] = infix[*i];
        (*i)++;
    }
    postfix[(*j)++] = ' ';
    (*i)--;
}

void handleInfixParenthesis(Stack *s, char *postfix, int *j) {
    double value;
    while (!isEmpty(s) && peek(s) != '(') {
        if (pop(s, &value) == STACK_UNDERFLOW) {
            HANDLE_ERROR("Stack underflow", 0);
            return;
        }
        postfix[(*j)++] = (char)value;
        postfix[(*j)++] = ' ';
    }
    if (isEmpty(s) || peek(s) != '(') {
        HANDLE_ERROR("Mismatched parentheses", 0);
        return;
    }
    pop(s, &value);
}

void handleInfixOperator(Stack *s, char *postfix, int *j, char operator) {
    double value;
    while (!isEmpty(s) && precedence(peek(s)) >= precedence(operator)) {
        if (pop(s, &value) == STACK_UNDERFLOW) {
            HANDLE_ERROR("Stack underflow", 0);
            return;
        }
        postfix[(*j)++] = (char)value;
        postfix[(*j)++] = ' ';
    }
    if (push(s, operator) == STACK_OVERFLOW) {
        HANDLE_ERROR("Stack overflow", 0);
    }
}

// Remove the duplicate definition of isValidCharacter
// int isValidCharacter(char ch) {
//     return isdigit(ch) || isxdigit(ch) || strchr("+-*/^() ", ch);
// }

// Remove the duplicate definition of handlePostfixOperand
// void handlePostfixOperand(const char *token, double *stack, int *top) {
//     if (isBinary(token)) {
//         stack[++(*top)] = binaryToDecimal(token);
//     } else if (isHexadecimal(token)) {
//         stack[++(*top)] = hexadecimalToDecimal(token);
//     } else {
//         stack[++(*top)] = atof(token);
//     }
// }