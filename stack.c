#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

// Initialize the stack by setting the top index to -1 and allocating memory
void initStack(Stack *s, int capacity)
{
    s->top = -1; // No elements in the stack
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
    if (isFull(s))
    {
        s->capacity *= 2;
        s->items = (double *)realloc(s->items, s->capacity * sizeof(double));
        if (s->items == NULL)
        {
            fprintf(stderr, "Error: Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
    }
    s->items[++s->top] = value;
}

// Pop an element from the stack -> remove the top element (LIFO)
double pop(Stack *s)
{
    if (!isEmpty(s))
    {
        return s->items[s->top--];
    }
    fprintf(stderr, "Error: Stack underflow\n");
    exit(EXIT_FAILURE); // Exit the program with an error code
}

// Peek the top element of the stack
double peek(Stack *s)
{
    if (!isEmpty(s))
    {
        return s->items[s->top];
    }
    return 0.0;
}

// Free the allocated memory of the stack
void freeStack(Stack *s)
{
    free(s->items);
    s->items = NULL;
    s->top = -1;
    s->capacity = 0;
}

// Function to check if a character is valid
int isValidCharacter(char ch)
{
    return isdigit(ch) || ch == '.' || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^' || ch == '(' || ch == ')' || ch == 's' || ch == 'l' || ch == 'S' || ch == 'C' || ch == 'T' || ch == ' ';
}

// Function to check if the input is binary
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

// Function to check if the input is decimal
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

// Function to check if the input is hexadecimal
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

// Function to convert input to decimal
int convertToDecimal(const char *input)
{
    if (isBinary(input))
    {
        return binaryToDecimal(input);
    }
    else if (isDecimal(input))
    {
        return atoi(input);
    }
    else if (isHexadecimal(input))
    {
        return hexadecimalToDecimal(input);
    }
    else
    {
        fprintf(stderr, "Error: Invalid input format\n");
        exit(EXIT_FAILURE);
    }
}