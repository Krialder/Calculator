#ifndef STACK_H
#define STACK_H

typedef struct {
    double *data;
    int top;
    int size;
} Stack;

void initStack(Stack *s, int size);
void freeStack(Stack *s);
int push(Stack *s, double value); // Changed return type to int
int pop(Stack *s, double *value); // Changed return type to int and added double* parameter
double peek(Stack *s);
int isEmpty(Stack *s);
int isFull(Stack *s);

#endif // STACK_H
