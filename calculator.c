#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "calculator.h"
#include "operator.h"
#include "operand.h"
#include "expression_conversion.h"
#include "common.h" // Include common.h
#include "declarations.h" // Include declarations.h

void handleOperator(Stack *ops, Stack *values, char op) {
    while (!isEmpty(ops) && precedence(peek(ops)) >= precedence(op)) {
        if (isEmpty(values)) {
            HANDLE_ERROR("Invalid infix expression: missing operand", 0);
            freeStack(values);
            freeStack(ops);
            return;
        }
        double val2, val1;
        if (pop(values, &val2) == STACK_UNDERFLOW || pop(values, &val1) == STACK_UNDERFLOW) {
            HANDLE_ERROR("Invalid infix expression: missing operand", 0);
            freeStack(values);
            freeStack(ops);
            return;
        }
        double operator;
        if (pop(ops, &operator) == STACK_UNDERFLOW) {
            HANDLE_ERROR("Invalid infix expression: missing operator", 0);
            freeStack(values);
            freeStack(ops);
            return;
        }
        if (push(values, applyOperation(val1, val2, (char)operator)) == STACK_OVERFLOW) {
            HANDLE_ERROR("Stack overflow", 0);
        }
    }
    if (push(ops, op) == STACK_OVERFLOW) {
        HANDLE_ERROR("Stack overflow", 0);
    }
}

void handleParentheses(Stack *ops, Stack *values) {
    double val1, val2;
    while (!isEmpty(ops) && peek(ops) != '(') {
        if (isEmpty(values)) {
            HANDLE_ERROR("Mismatched parentheses", 0);
            freeStack(values);
            freeStack(ops);
            return;
        }
        if (pop(values, &val2) == STACK_UNDERFLOW || pop(values, &val1) == STACK_UNDERFLOW) {
            HANDLE_ERROR("Mismatched parentheses", 0);
            freeStack(values);
            freeStack(ops);
            return;
        }
        double op;
        if (pop(ops, &op) == STACK_UNDERFLOW) {
            HANDLE_ERROR("Mismatched parentheses", 0);
            freeStack(values);
            freeStack(ops);
            return;
        }
        push(values, applyOperation(val1, val2, (char)op));
    }
    if (isEmpty(ops)) {
        HANDLE_ERROR("Mismatched parentheses", 0);
        freeStack(values);
        freeStack(ops);
        return;
    }
    double op;
    if (pop(ops, &op) == STACK_UNDERFLOW) {
        HANDLE_ERROR("Mismatched parentheses", 0);
        freeStack(values);
        freeStack(ops);
        return;
    }
}

double evaluateInfix(char *infix) {
    Stack ops;
    Stack values;
    initStack(&values, 100);
    initStack(&ops, 100);

    for (int i = 0; infix[i] != '\0'; i++) {
        if (!isValidCharacter(infix[i])) {
            HANDLE_ERROR("Invalid character in infix expression", 0);
            freeStack(&values);
            freeStack(&ops);
            return NAN;
        }
        if (isdigit(infix[i]) || infix[i] == '.' || isxdigit(infix[i])) {
            char operand[20];
            int j = 0;
            while (isdigit(infix[i]) || infix[i] == '.' || isxdigit(infix[i])) {
                operand[j++] = infix[i++];
            }
            operand[j] = '\0';
            if (push(&values, convertToDecimal(operand)) == STACK_OVERFLOW) {
                HANDLE_ERROR("Stack overflow", 0);
            }
            i--;
        } else if (infix[i] == '(') {
            if (push(&ops, infix[i]) == STACK_OVERFLOW) {
                HANDLE_ERROR("Stack overflow", 0);
            }
        } else if (infix[i] == ')') {
            handleParentheses(&ops, &values);
        } else if (isOperator(infix[i])) {
            handleOperator(&ops, &values, infix[i]);
        } else if (!isspace(infix[i])) {
            HANDLE_ERROR("Invalid character in expression", 0);
            freeStack(&values);
            freeStack(&ops);
            return NAN;
        }
    }

    while (!isEmpty(&ops)) {
        if (isEmpty(&values)) {
            HANDLE_ERROR("Invalid infix expression: missing operand", 0);
            freeStack(&values);
            freeStack(&ops);
            return NAN;
        }
        double val2, val1;
        if (pop(&values, &val2) == STACK_UNDERFLOW || pop(&values, &val1) == STACK_UNDERFLOW) {
            HANDLE_ERROR("Invalid infix expression: missing operand", 0);
            freeStack(&values);
            freeStack(&ops);
            return NAN;
        }
        double op;
        if (pop(&ops, &op) == STACK_UNDERFLOW) {
            HANDLE_ERROR("Invalid infix expression: missing operator", 0);
            freeStack(&values);
            freeStack(&ops);
            return NAN;
        }
        if (push(&values, applyOperation(val1, val2, (char)op)) == STACK_OVERFLOW) {
            HANDLE_ERROR("Stack overflow", 0);
        }
    }

    if (isEmpty(&values)) {
        HANDLE_ERROR("Invalid infix expression: missing result", 0);
        freeStack(&values);
        freeStack(&ops);
        return NAN;
    }
    double result;
    if (pop(&values, &result) == STACK_UNDERFLOW) {
        HANDLE_ERROR("Invalid infix expression: missing result", 0);
        freeStack(&values);
        freeStack(&ops);
        return NAN;
    }
    if (!isEmpty(&values)) {
        HANDLE_ERROR("Invalid infix expression: extra operands", 0);
        freeStack(&values);
        freeStack(&ops);
        return NAN;
    }

    freeStack(&values);
    freeStack(&ops);

    char postfix[200];
    infixToPostfix(infix, postfix);

    result = evaluatePostfix(postfix);
    if (isnan(result)) {
        HANDLE_ERROR("Invalid infix expression: evaluation failed", 0);
    }

    return result;
}