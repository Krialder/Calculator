#ifndef STACK_H
#define STACK_H

// Define the stack structure
typedef struct
{
    // Pointer to dynamically allocated array to store stack elements
    double *items;
    // Index of the top element
    int top;
    // Current capacity of the stack
    int capacity;
} Stack;

// Function to initialize the stack
void initStack(Stack *s, int capacity);

// Function to check if the stack is empty
int isEmpty(Stack *s);

// Function to check if the stack is full
int isFull(Stack *s);

// Function to push an element into the stack
void push(Stack *s, double value);

// Function to pop an element from the stack
double pop(Stack *s);

// Function to peek the top element of the stack
double peek(Stack *s);

// Function to free the allocated memory of the stack
void freeStack(Stack *s);

// Function to check if a character is valid
int isValidCharacter(char ch);

// Function to evaluate postfix expression
double evaluatePostfix(char *postfix);

// Function to check if the operator is right associative
int isRightAssociative(char op);

// Function to handle operands in the infix expression
void handleOperand(char *infix, char *postfix, int *i, int *j);

// Function to handle operators in the infix expression
void handleOperator(Stack *s, char *postfix, int *j, char op);

// Function to handle operands in the postfix expression
void handlePostfixOperand(Stack *s, char *postfix, int *i);

// Function to handle operators in the postfix expression
void handlePostfixOperator(Stack *s, char op);

#endif // STACK_H