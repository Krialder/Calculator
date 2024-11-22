#include "complex_operations.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "stack.h" // Include stack header

// Function to evaluate a postfix expression
Complex evaluatePostfix(const char* postfix) {
    Stack s;
    initStack(&s, 100);
    int i = 0;
    while (postfix[i] != '\0') {
        if (isdigit(postfix[i]) || postfix[i] == '.') {
            handlePostfixOperand(&s, postfix, &i);
        } else if (isOperator(postfix[i])) {
            handlePostfixOperator(&s, postfix[i]);
            i++;
        } else {
            i++;
        }
    }
    Complex result;
    pop(&s, &result);
    freeStack(&s);
    return result;
}

// Function to handle operands in postfix evaluation
void handlePostfixOperand(Stack* s, const char* postfix, int* i) {
    char buffer[100];
    int j = 0;
    while (isdigit(postfix[*i]) || postfix[*i] == '.') {
        buffer[j++] = postfix[(*i)++];
    }
    buffer[j] = '\0';
    Complex value;
    value.real = atof(buffer);
    value.imag = 0;
    push(s, value);
}

// Function to handle operators in postfix evaluation
void handlePostfixOperator(Stack* s, char op) {
    if (op == 's') // Square root
    {
        Complex val;
        pop(s, &val);
        Complex result = sqrtComplex(val); // Ensure sqrtComplex returns Complex
        push(s, result);
    }
    else if (op == 'l') // Logarithm base 10
    {
        Complex val;
        pop(s, &val);
        Complex result = logComplex(val);
        push(s, result);
    }
    else if (op == 'S') // Sine
    {
        Complex val;
        pop(s, &val);
        Complex result = sinComplex(val);
        push(s, result);
    }
    else if (op == 'C') // Cosine
    {
        Complex val;
        pop(s, &val);
        Complex result = cosComplex(val);
        push(s, result);
    }
    else if (op == 'T') // Tangent
    {
        Complex val;
        pop(s, &val);
        Complex result = tanComplex(val);
        push(s, result);
    }
    else if (op == 'e') // Exponential
    {
        Complex val;
        pop(s, &val);
        Complex result = expComplex(val);
        push(s, result);
    }
    else
    {
        Complex val2, val1;
        pop(s, &val2); // Pop two operands from the stack
        pop(s, &val1);
        Complex result = { 0, 0 };
        switch (op)
        {
            case '+': result = addComplex(val1, val2); break;
            case '-': result = subtractComplex(val1, val2); break; // Ensure subtractComplex returns Complex
            case '*': result = multiplyComplex(val1, val2); break;
            case '/': result = divideComplex(val1, val2); break;
            case '^': result = powerComplex(val1, val2); break;
        }
        push(s, result);
    }
}

Complex sqrtComplex(Complex c) {
    Complex result;
    double magnitude = sqrt(sqrt(c.real * c.real + c.imag * c.imag));
    double angle = atan2(c.imag, c.real) / 2;
    result.real = magnitude * cos(angle);
    result.imag = magnitude * sin(angle);
    return result;
}

Complex logComplex(Complex c) {
    Complex result;
    result.real = log(sqrt(c.real * c.real + c.imag * c.imag));
    result.imag = atan2(c.imag, c.real);
    return result;
}

Complex sinComplex(Complex c) {
    Complex result;
    result.real = sin(c.real) * cosh(c.imag);
    result.imag = cos(c.real) * sinh(c.imag);
    return result;
}

Complex cosComplex(Complex c) {
    Complex result;
    result.real = cos(c.real) * cosh(c.imag);
    result.imag = -sin(c.real) * sinh(c.imag);
    return result;
}

Complex tanComplex(Complex c) {
    Complex result;
    Complex numerator = sinComplex(c);
    Complex denominator = cosComplex(c);
    result.real = numerator.real / denominator.real;
    result.imag = numerator.imag / denominator.imag;
    return result;
}

Complex expComplex(Complex c) {
    Complex result;
    double expReal = exp(c.real);
    result.real = expReal * cos(c.imag);
    result.imag = expReal * sin(c.imag);
    return result;
}

Complex addComplex(Complex a, Complex b) {
    Complex result;
    result.real = a.real + b.real;
    result.imag = a.imag + b.imag;
    return result;
}

Complex subtractComplex(Complex a, Complex b) {
    Complex result;
    result.real = a.real - b.real;
    result.imag = a.imag - b.imag;
    return result;
}

Complex multiplyComplex(Complex a, Complex b) {
    Complex result;
    result.real = a.real * b.real - a.imag * b.imag;
    result.imag = a.real * b.imag + a.imag * b.real;
    return result;
}

Complex divideComplex(Complex a, Complex b) {
    Complex result;
    double denominator = b.real * b.real + b.imag * b.imag;
    result.real = (a.real * b.real + a.imag * b.imag) / denominator;
    result.imag = (a.imag * b.real - a.real * b.imag) / denominator;
    return result;
}

Complex powerComplex(Complex a, Complex b) {
    Complex result;
    double r = sqrt(a.real * a.real + a.imag * a.imag);
    double theta = atan2(a.imag, a.real);
    double new_r = pow(r, b.real) * exp(-b.imag * theta);
    double new_theta = b.real * theta + b.imag * log(r);
    result.real = new_r * cos(new_theta);
    result.imag = new_r * sin(new_theta);
    return result;
}
