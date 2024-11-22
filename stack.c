#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Initialize the stack by setting the top index to -1 and allocating memory
int initStack(Stack *s, int capacity)
{
    s->top = -1; // No elements in the stack
    s->capacity = capacity;
    s->items = (Complex *)malloc(capacity * sizeof(Complex));
    if (s->items == NULL)
    {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return -1;
    }
    return 0;
}

// Check if the stack is empty
int isEmpty(const Stack *s)
{
    return s->top == -1; // Return 1 if the stack is empty, otherwise 0
}

// Check if the stack is full
int isFull(const Stack *s)
{
    return s->top == s->capacity - 1; // Return 1 if the stack is full, otherwise 0
}

// Push an element onto the stack
int push(Stack *s, Complex value)
{
    if (isFull(s))
    {
        // Double the capacity if the stack is full
        s->capacity *= 2;
        s->items = (Complex *)realloc(s->items, s->capacity * sizeof(Complex));
        if (s->items == NULL)
        {
            // Print an error message and return -1 if memory allocation fails
            fprintf(stderr, "Error: Memory allocation failed\n");
            return -1;
        }
    }
    s->items[++s->top] = value; // Add the new element to the top of the stack
    return 0;
}

// Pop an element from the stack -> remove the top element (LIFO)
int pop(Stack *s, Complex *value)
{
    if (isEmpty(s))
    {
        fprintf(stderr, "Error: Stack underflow\n");
        return -1; // Return -1 if the stack is empty
    }
    *value = s->items[s->top--]; // Remove and return the top element
    return 0;
}

// Peek at the top element of the stack without removing it
int peek(const Stack *s, Complex *value)
{
    if (isEmpty(s))
    {
        fprintf(stderr, "Error: Stack is empty\n");
        return -1; // Return -1 if the stack is empty
    }
    *value = s->items[s->top];
    return 0;
}

// Free the allocated memory of the stack
void freeStack(Stack *s)
{
    if (s->items != NULL)
    {
        free(s->items); // Free the memory allocated for the stack elements
        s->items = NULL; // Set the pointer to NULL
    }
    s->top = -1; // Reset the top index
    s->capacity = 0; // Reset the capacity
}