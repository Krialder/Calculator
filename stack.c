#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

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
    return s->top == -1; // Return 1 if the stack is empty, otherwise 0
}

// Check if the stack is full
int isFull(Stack *s)
{
    return s->top == s->capacity - 1; // Return 1 if the stack is full, otherwise 0
}

// Push an element onto the stack
void push(Stack *s, double value)
{
    if (isFull(s))
    {
        // Double the capacity if the stack is full
        s->capacity *= 2;
        s->items = (double *)realloc(s->items, s->capacity * sizeof(double));
        if (s->items == NULL)
        {
            // Print an error message and exit if memory allocation fails
            fprintf(stderr, "Error: Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
    }
    s->items[++s->top] = value; // Add the new element to the top of the stack
}

// Pop an element from the stack -> remove the top element (LIFO)
double pop(Stack *s)
{
    if (!isEmpty(s))
    {
        return s->items[s->top--]; // Remove and return the top element
    }
    fprintf(stderr, "Error: Stack underflow\n");
    exit(EXIT_FAILURE); // Exit the program with an error code
}


double peek(Stack *s)
{
    if (!isEmpty(s))
    {
        return s->items[s->top]; 
    }
    return 0.0; // Return 0.0 if the stack is empty
}

// Free the allocated memory of the stack
void freeStack(Stack *s)
{
    free(s->items); // Free the memory allocated for the stack elements
    s->items = NULL; // Set the pointer to NULL
    s->top = -1; // Reset the top index
    s->capacity = 0; // Reset the capacity
}

// Function to check if a character is valid for the calculator
int isValidCharacter(char ch)
{
    // Return 1 if the character is a digit, decimal point, operator, or parenthesis
    return isdigit(ch) || ch == '.' || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^' || ch == '(' || ch == ')' || ch == 's' || ch == 'l' || ch == 'S' || ch == 'C' || ch == 'T' || ch == ' ';
}

// Function to check if the input is a binary number
int isBinary(const char *input)
{
    for (int i = 0; input[i] != '\0'; i++)
    {
        if (input[i] != '0' && input[i] != '1')
        {
            return 0; // Return 0 if any character is not '0' or '1'
        }
    }
    return 1; // Return 1 if all characters are '0' or '1'
}

// Function to check if the input is a decimal number
int isDecimal(const char *input)
{
    for (int i = 0; input[i] != '\0'; i++)
    {
        if (!isdigit(input[i]))
        {
            return 0; // Return 0 if any character is not a digit
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
            return 0; // Return 0 if any character is not a hexadecimal digit
        }
    }
    return 1; 
}

// Function to convert input to a decimal number
int convertToDecimal(const char *input)
{
    if (isBinary(input))
    {
        return binaryToDecimal(input); // Convert binary input to decimal
    }
    else if (isDecimal(input))
    {
        return atoi(input); // Convert decimal input to integer
    }
    else if (isHexadecimal(input))
    {
        return hexadecimalToDecimal(input); // Convert hexadecimal input to decimal
    }
    else
    {
        fprintf(stderr, "Error: Invalid input format\n");
        exit(EXIT_FAILURE);
    }
}