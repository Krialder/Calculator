#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "conversion.h"
#include <string.h>
#include <math.h> // Include math.h for mathematical functions

// Initialize the stack by setting the top index to -1 and allocating memory
void initStack(Stack *s, int capacity)
{
    if (capacity <= 0)
    {
        fprintf(stderr, "Error: Invalid stack capacity\n");
        exit(EXIT_FAILURE);
    }
    s->top = -1;
    s->capacity = capacity;
    s->items = (double *)malloc(capacity * sizeof(double));
    if (s->items == NULL)
    {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
}

// Check if the stack is empty
int isEmpty(Stack *s)
{
    return s->top == -1;
}

// Check if the stack is full
int isFull(Stack *s)
{
    return s->top == s->capacity - 1;
}

// Push an element onto the stack
void push(Stack *s, double value)
{
    if (isnan(value) || isinf(value))
    {
        fprintf(stderr, "Error: Invalid value\n");
        exit(EXIT_FAILURE);
    }
    if (isFull(s))
    {
        s->capacity *= 2;
        double *newItems = (double *)realloc(s->items, s->capacity * sizeof(double));
        if (newItems == NULL)
        {
            fprintf(stderr, "Error: Memory allocation failed\n");
            free(s->items); // Free the old memory to prevent memory leak
            exit(EXIT_FAILURE);
        }
        s->items = newItems;
    }
    s->items[++s->top] = value;
}

// Pop an element from the stack
double pop(Stack *s)
{
    if (isEmpty(s))
    {
        fprintf(stderr, "Error: Stack underflow\n");
        exit(EXIT_FAILURE);
    }
    return s->items[s->top--];
}

double peek(Stack *s)
{
    if (isEmpty(s))
    {
        fprintf(stderr, "Error: Stack underflow\n");
        exit(EXIT_FAILURE);
    }
    return s->items[s->top];
}

// Free the allocated memory of the stack
void freeStack(Stack *s)
{
    if (s->items != NULL)
    {
        free(s->items);
        s->items = NULL;
    }
    s->top = -1;
    s->capacity = 0;
}

// Function to check if a character is valid for the calculator
int isValidCharacter(char ch)
{
    return isdigit(ch) || ch == '.' || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^' || ch == '(' || ch == ')' || ch == 's' || ch == 'l' || ch == 'S' || ch == 'C' || ch == 'T' || ch == ' ' || isxdigit(ch);
}

// Function to check if the input is a binary number
int isBinary(const char *input)
{
    for (int i = 0; input[i] != '\0'; i++)
    {
        if (input[i] != '0' && input[i] != '1')
        {
            return 0;
        }
    }
    return 1;
}

// Function to check if the input is a decimal number
int isDecimal(const char *input)
{
    for (int i = 0; input[i] != '\0'; i++)
    {
        if (!isdigit(input[i]))
        {
            return 0;
        }
    }
    return 1;
}

// Function to check if the input is a hexadecimal number
int isHexadecimal(const char *input)
{
    for (int i = 0; input[i] != '\0'; i++)
    {
        if (!isxdigit(input[i]))
        {
            return 0;
        }
    }
    return 1;
}

int isNegativeBinary(const char *input)
{
    return input[0] == '-' && isBinary(input + 1);
}

int isNegativeHexadecimal(const char *input)
{
    return input[0] == '-' && isHexadecimal(input + 1);
}

int isNegativeDecimal(const char *input)
{
    return input[0] == '-' && isDecimal(input + 1);
}

int convertNegativeBinaryToDecimal(const char *input)
{
    if (!isNegativeBinary(input))
    {
        fprintf(stderr, "Error: Invalid negative binary input\n");
        exit(EXIT_FAILURE);
    }
    return -binaryToDecimal(input + 1);
}

int convertNegativeHexadecimalToDecimal(const char *input)
{
    if (!isNegativeHexadecimal(input))
    {
        fprintf(stderr, "Error: Invalid negative hexadecimal input\n");
        exit(EXIT_FAILURE);
    }
    return -hexadecimalToDecimal(input + 1);
}

int convertNegativeDecimalToDecimal(const char *input)
{
    if (!isNegativeDecimal(input))
    {
        fprintf(stderr, "Error: Invalid negative decimal input\n");
        exit(EXIT_FAILURE);
    }
    return -atoi(input + 1);
}

int isOctal(const char *input)
{
    for (int i = 0; input[i] != '\0'; i++)
    {
        if (input[i] < '0' || input[i] > '7')
        {
            return 0;
        }
    }
    return 1;
}

int isNegativeOctal(const char *input)
{
    return input[0] == '-' && isOctal(input + 1);
}

int convertNegativeOctalToDecimal(const char *input)
{
    if (!isNegativeOctal(input))
    {
        fprintf(stderr, "Error: Invalid negative octal input\n");
        exit(EXIT_FAILURE);
    }
    return -octalToDecimal(input + 1);
}

// Function to convert input to a decimal number
int convertToDecimal(const char *input)
{
    if (isNegativeBinary(input))
    {
        return convertNegativeBinaryToDecimal(input);
    }
    else if (isBinary(input))
    {
        return binaryToDecimal(input);
    }
    else if (isDecimal(input))
    {
        return atoi(input);
    }
    else if (isNegativeHexadecimal(input))
    {
        return convertNegativeHexadecimalToDecimal(input);
    }
    else if (isHexadecimal(input))
    {
        return hexadecimalToDecimal(input);
    }
    else if (isNegativeDecimal(input))
    {
        return convertNegativeDecimalToDecimal(input);
    }
    else if (isNegativeOctal(input))
    {
        return convertNegativeOctalToDecimal(input);
    }
    else if (isOctal(input))
    {
        return octalToDecimal(input);
    }
    else
    {
        fprintf(stderr, "Error: Invalid input format\n");
        exit(EXIT_FAILURE);
    }
}

int precedence(char op);

double applyOperation(double a, double b, char op) 
{
    switch (op) 
    {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        case '^': return pow(a, b);
        case 's': return sqrt(a);
        case 'l': return log10(a);
        case 'S': return sin(a);
        case 'C': return cos(a);
        case 'T': return tan(a);
        default: return 0;
    }
}

void handleParentheses(Stack *ops, Stack *values) 
{
    while (!isEmpty(ops) && peek(ops) != '(') 
    {
        if (isEmpty(values))
        {
            fprintf(stderr, "Error: Mismatched parentheses\n");
            exit(EXIT_FAILURE);
        }
        double val2 = pop(values);
        double val1 = pop(values);
        char op = (char)pop(ops);
        push(values, applyOperation(val1, val2, op));
    }
    if (isEmpty(ops))
    {
        fprintf(stderr, "Error: Mismatched parentheses\n");
        exit(EXIT_FAILURE);
    }
    pop(ops); // Remove the '(' from the stack
}