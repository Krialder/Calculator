#ifndef STACK_H
#define STACK_H

typedef struct
{
    // Pointer to dynamically allocated array to store stack elements
    double *items;
    // Index of the top element
    int top;
    // Current capacity of the stack
    int capacity;
} Stack;

// Function to initialize the stack with a given capacity
// This function sets up the stack and allocates memory for it
void initStack(Stack *s, int capacity); 

// Function to check if the stack is empty
// Returns 1 if the stack is empty, otherwise returns 0
int isEmpty(Stack *s);

// Function to check if the stack is full
int isFull(Stack *s);

// Function to push an element into the stack
// Adds a new element to the top of the stack
void push(Stack *s, double value); 

// Function to pop an element from the stack
// Removes and returns the top element of the stack
double pop(Stack *s); 

// Function to peek the top element of the stack without removing it
// Returns the top element of the stack
double peek(Stack *s);

// Function to free the allocated memory of the stack
void freeStack(Stack *s);

// Function to check if a character is valid for the calculator
int isValidCharacter(char ch);

// Function to evaluate a postfix expression
double evaluatePostfix(char *postfix);

// Function to check if the input is a binary number
int isBinary(const char *input);

// Function to check if the input is a decimal number
int isDecimal(const char *input);

// Function to check if the input is a hexadecimal number
int isHexadecimal(const char *input);

// Function to convert input to a decimal number
int convertToDecimal(const char *input);

#endif // STACK_H