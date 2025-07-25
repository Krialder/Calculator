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
#include "error.h"


double evaluateInfix(char *infix) {
    Stack ops;
    Stack values;
    initStack(&values, sizeof(double));
    initStack(&ops, sizeof(char));
    while (!isEmpty(&ops)) {
        if (isEmpty(&values)) {
            handleError("Invalid infix expression");
        }
        double val2 = pop(&values);
        if (isEmpty(&values)) {
            handleError("Invalid infix expression");
        }
        double val1 = pop(&values);
        char op = (char)pop(&ops);
        push(&values, applyOperation(val1, val2, op));
    }
    if (isEmpty(&values)) {
        handleError("Invalid infix expression");
    }
    double result = pop(&values);
    if (!isEmpty(&values)) {
        handleError("Invalid infix expression");
    }
    return result;
}