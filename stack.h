#ifndef STACK_H
#define STACK_H

typedef struct 
{
    double *items;
    int top;
    int capacity;
} Stack;

// Function declarations for stack operations
void initStack(Stack *s, int capacity);
int isEmpty(Stack *s);
int isFull(Stack *s);
void push(Stack *s, double value);
double pop(Stack *s);
double peek(Stack *s);
void freeStack(Stack *s);

#endif // STACK_H

