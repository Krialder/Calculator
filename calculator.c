#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include "stack.h"
#include "calculator.h"

// Get the precedence of the operator
int precedence(char op)
{
    switch (op)
    {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        case 's': // Square root
        case 'l': // Logarithm
        case 'S': // Sine
        case 'C': // Cosine
        case 'T': // Tangent
            return 4;
        default:
            return 0;
    }
}

// Check if the character is an operator
int isOperator(char ch)
{
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^' || ch == 's' || ch == 'l' || ch == 'S' || ch == 'C' || ch == 'T';
}

// Check if the operator is right associative
int isRightAssociative(char op)
{
    return op == '^';
}

// Handle operands in the infix expression
void handleOperand(char *infix, char *postfix, int *i, int *j)
{
    while (isdigit(infix[*i]) || infix[*i] == '.')
    {
        postfix[(*j)++] = infix[(*i)++];
    }
    postfix[(*j)++] = ' '; // Add space to separate operands
}

// Handle operators in the infix expression
void handleOperator(Stack *s, char *postfix, int *j, char op)
{
    while (!isEmpty(s) && precedence(peek(s)) > precedence(op) || 
           (!isEmpty(s) && precedence(peek(s)) == precedence(op) && !isRightAssociative(op)))
    {
        postfix[(*j)++] = pop(s);
        postfix[(*j)++] = ' ';
    }
    push(s, op);
}

// Convert the infix expression to postfix expression using the shunting-yard algorithm
void infixToPostfix(char *infix, char *postfix)
{
    Stack s;
    initStack(&s, MAX);
    int i = 0, j = 0;
    while (infix[i] != '\0')
    {
        if (isdigit(infix[i]) || infix[i] == '.')
        {
            handleOperand(infix, postfix, &i, &j);
        }
        else if (infix[i] == '(')
        {
            push(&s, infix[i++]); // Push the opening parenthesis to the stack
        }
        else if (infix[i] == ')')
        {
            while (!isEmpty(&s) && peek(&s) != '(')
            {
                postfix[j++] = pop(&s); // Pop operators from the stack and add them to the postfix expression until an opening parenthesis is found
                postfix[j++] = ' ';
            }
            pop(&s); // Pop the opening parenthesis from the stack
            i++;
        }
        else if (isOperator(infix[i]))
        {
            handleOperator(&s, postfix, &j, infix[i++]);
        }
    }
    while (!isEmpty(&s))
    {
        postfix[j++] = pop(&s); // Pop the remaining operators from the stack and add them to the postfix expression
        postfix[j++] = ' ';
    }
    postfix[j - 1] = '\0'; // Null-terminate the postfix expression
    freeStack(&s);
}

// Handle operands in the postfix expression
void handlePostfixOperand(Stack *s, char *postfix, int *i)
{
    double num = 0;
    double decimal = 0.1;
    int isDecimal = 0;
    while (isdigit(postfix[*i]) || postfix[*i] == '.')
    {
        if (postfix[*i] == '.')
        {
            isDecimal = 1;
            (*i)++;
            continue;
        }
        if (isDecimal)
        {
            num += (postfix[*i] - '0') * decimal;
            decimal /= 10;
        }
        else
        {
            num = num * 10 + (postfix[*i] - '0');
        }
        (*i)++;
    }
    push(s, num); // Push the operand to the stack
}

// Handle operators in the postfix expression
void handlePostfixOperator(Stack *s, char op)
{
    if (op == 's') // Square root
    {
        double val = pop(s);
        push(s, sqrt(val));
    }
    else if (op == 'l') // Logarithm base 10
    {
        double val = pop(s);
        push(s, log10(val));
    }
    else if (op == 'S') // Sine
    {
        double val = pop(s);
        push(s, sin(val));
    }
    else if (op == 'C') // Cosine
    {
        double val = pop(s);
        push(s, cos(val));
    }
    else if (op == 'T') // Tangent
    {
        double val = pop(s);
        push(s, tan(val));
    }
    else
    {
        double val2 = pop(s); // Pop two operands from the stack
        double val1 = pop(s);
        switch (op)
        {
            case '+': push(s, val1 + val2); break;
            case '-': push(s, val1 - val2); break;
            case '*': push(s, val1 * val2); break;
            case '/':
                if (val2 == 0)
                {
                    fprintf(stderr, "Error: Division by zero\n");
                    exit(EXIT_FAILURE);
                }
                push(s, val1 / val2);
                break;
            case '^': push(s, pow(val1, val2)); break;
        }
    }
}

// Evaluate the postfix expression
double evaluatePostfix(char *postfix)
{
    Stack s;
    initStack(&s, MAX);
    int i = 0;
    while (postfix[i] != '\0')
    {
        if (isdigit(postfix[i]) || postfix[i] == '.')
        {
            handlePostfixOperand(&s, postfix, &i);
        }
        else if (isOperator(postfix[i]))
        {
            handlePostfixOperator(&s, postfix[i]);
            i++;
        }
        else
        {
            i++; // Skip spaces
        }
    }
    if (isEmpty(&s))
    {
        fprintf(stderr, "Error: Invalid postfix expression\n");
        exit(EXIT_FAILURE);
    }

    double result = pop(&s); // The result of the expression is the only element left in the stack

    if (!isEmpty(&s))
    {
        fprintf(stderr, "Error: Invalid postfix expression\n");
        exit(EXIT_FAILURE);
    }

    freeStack(&s);
    return result;
}

// Function to convert a binary string to a decimal number
int binaryToDecimal(const char *binary)
{
    int decimal = 0;
    int length = strlen(binary);
    for (int i = 0; i < length; i++)
    {
        if (binary[length - i - 1] == '1')
        {
            decimal += pow(2, i);
        }
    }
    return decimal;
}

// Function to convert a decimal number to a binary string
void decimalToBinary(int decimal, char *binary)
{
    int index = 0;
    while (decimal > 0)
    {
        binary[index++] = (decimal % 2) + '0';
        decimal /= 2;
    }
    binary[index] = '\0';
    // Reverse the binary string
    for (int i = 0; i < index / 2; i++)
    {
        char temp = binary[i];
        binary[i] = binary[index - i - 1];
        binary[index - i - 1] = temp;
    }
}

// Function to convert a hexadecimal string to a decimal number
int hexadecimalToDecimal(const char *hex)
{
    int decimal = 0;
    int length = strlen(hex);
    for (int i = 0; i < length; i++)
    {
        char digit = hex[length - i - 1];
        if (digit >= '0' && digit <= '9')
        {
            decimal += (digit - '0') * pow(16, i);
        }
        else if (digit >= 'A' && digit <= 'F')
        {
            decimal += (digit - 'A' + 10) * pow(16, i);
        }
        else if (digit >= 'a' && digit <= 'f')
        {
            decimal += (digit - 'a' + 10) * pow(16, i);
        }
    }
    return decimal;
}

// Function to convert a decimal number to a hexadecimal string
void decimalToHexadecimal(int decimal, char *hex)
{
    int index = 0;
    while (decimal > 0)
    {
        int remainder = decimal % 16;
        if (remainder < 10)
        {
            hex[index++] = remainder + '0';
        }
        else
        {
            hex[index++] = remainder - 10 + 'A';
        }
        decimal /= 16;
    }
    hex[index] = '\0';
    // Reverse the hexadecimal string
    for (int i = 0; i < index / 2; i++)
    {
        char temp = hex[i];
        hex[i] = hex[index - i - 1];
        hex[index - i - 1] = temp;
    }
}