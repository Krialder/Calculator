#ifndef STACK_H
#define STACK_H

#include "calculator.h" // Include the header file where Complex and Stack are defined
#include "config.h" // Include the configuration header file

// Function prototypes for stack operations
int initStack(Stack* s, int capacity);
int isEmpty(const Stack* s);
int isFull(const Stack* s);
int push(Stack* s, Complex value);
int pop(Stack* s, Complex* value);
int peek(const Stack* s, Complex* value);
void freeStack(Stack* s);

#endif // STACK_H