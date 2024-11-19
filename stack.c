#include "stack.h"
#include "common.h" // Include common.h
#include "declarations.h" // Include declarations.h
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "conversion.h"
#include <string.h>
#include <math.h>

#define SUCCESS 0

void initStack(Stack *s, int size) {
    s->data = (double *)malloc(size * sizeof(double));
    if (s->data == NULL) {
        HANDLE_ERROR("Memory allocation failed for stack", 0);
    }
    s->top = -1;
    s->size = size;
}

void freeStack(Stack *s) {
    free(s->data);
    s->data = NULL;
    s->top = -1;
    s->size = 0;
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

int isFull(Stack *s) {
    return s->top == s->size - 1;
}

int push(Stack *s, double value) {
    if (isFull(s)) {
        HANDLE_ERROR("Stack overflow", 0);
        return STACK_OVERFLOW;
    }
    s->data[++(s->top)] = value;
    return 0;
}

int pop(Stack *s, double *value) {
    if (isEmpty(s)) {
        HANDLE_ERROR("Stack underflow", 0);
        return STACK_UNDERFLOW;
    }
    *value = s->data[(s->top)--];
    return 0;
}

double peek(Stack *s) {
    if (isEmpty(s)) {
        HANDLE_ERROR("Stack is empty", 0);
        return NAN;
    }
    return s->data[s->top];
}

void pushChar(Stack *s, char value) {
    if (isFull(s)) {
        HANDLE_ERROR("Stack overflow", 0);
        return;
    }
    s->data[++(s->top)] = value;
}

int isNegativeDecimal(const char *input) {
    if (input[0] != '-') {
        HANDLE_ERROR("Invalid input", 0);
        return 0;
    }
    return isDecimal(input + 1);
}

int convertNegativeBinaryToDecimal(const char *input) {
    if (input[0] != '-') {
        HANDLE_ERROR("Invalid input", 0);
        return 0;
    }
    return -binaryToDecimal(input + 1);
}

int convertNegativeHexadecimalToDecimal(const char *input) {
    if (input[0] != '-') {
        HANDLE_ERROR("Invalid input", 0);
        return 0;
    }
    return -hexadecimalToDecimal(input + 1);
}

int convertNegativeDecimalToDecimal(const char *input) {
    if (input[0] != '-') {
        HANDLE_ERROR("Invalid negative decimal input", 0);
        return 0;
    }
    return -atoi(input + 1);
}

int isOctal(const char *input) {
    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] < '0' || input[i] > '7') {
            HANDLE_ERROR("Invalid input", 0);
            return 0;
        }
    }
    return 1;
}

int isNegativeOctal(const char *input) {
    if (input[0] != '-') {
        HANDLE_ERROR("Invalid input", 0);
        return 0;
    }
    return isOctal(input + 1);
}

int convertNegativeOctalToDecimal(const char *input) {
    if (input[0] != '-') {
        HANDLE_ERROR("Invalid negative octal input", 0);
        return 0;
    }
    return -octalToDecimal(input + 1);
}

int octalToDecimal(const char *octal) {
    if (octal == NULL || *octal == '\0') {
        HANDLE_ERROR("Invalid input", 0);
        return 0;
    }
    int decimal = 0;
    int length = strlen(octal);
    for (int i = 0; i < length; i++) {
        if (octal[length - i - 1] >= '0' && octal[length - i - 1] <= '7') {
            decimal += (octal[length - i - 1] - '0') * pow(8, i);
        } else {
            HANDLE_ERROR("Invalid octal number", 0);
            return 0;
        }
    }
    return decimal;
}