#ifndef COMPLEX_OPERATIONS_H
#define COMPLEX_OPERATIONS_H

#include "calculator.h" // Include the header file where Complex is defined

// Function to evaluate a postfix expression
Complex evaluatePostfix(const char* postfix);

// Function to handle operands in postfix evaluation
void handlePostfixOperand(Stack* s, const char* postfix, int* i);

// Function to handle operators in postfix evaluation
void handlePostfixOperator(Stack* s, char op); // Add this declaration

Complex sqrtComplex(Complex c);
Complex logComplex(Complex c);
Complex sinComplex(Complex c);
Complex cosComplex(Complex c);
Complex tanComplex(Complex c);
Complex expComplex(Complex c);
Complex addComplex(Complex a, Complex b);
Complex subtractComplex(Complex a, Complex b);
Complex multiplyComplex(Complex a, Complex b);
Complex divideComplex(Complex a, Complex b);
Complex powerComplex(Complex a, Complex b);

#endif // COMPLEX_OPERATIONS_H
