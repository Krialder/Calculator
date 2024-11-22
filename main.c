#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "calculator.h"
#include "conversion.h"
#include "stack.h"
#include "utils.h"
#include "config.h"
#include "complex_operations.h" // Include the new header

void convertOperands(char *input); // Add this declaration

int main()
{
    char input[MAX];
    char resultTypes[MAX];
    char postfix[MAX];
    char result[MAX];
    char* token;
    Stack stack;
    if (initStack(&stack, MAX) != 0)
    {
        fprintf(stderr, "Failed to initialize stack\n");
        return EXIT_FAILURE;
    }

    printf("Enter the numbers with their types and operators (e.g., b1010 (+) d5 (-) hA). Supported operators: +, -, *, /, ^, s (sqrt), l (log), S (sin), C (cos), T (tan), e (exp): ");
    if (fgets(input, MAX, stdin) == NULL)
    {
        fprintf(stderr, "Failed to read input\n");
        freeStack(&stack);
        return EXIT_FAILURE;
    }
    input[strcspn(input, "\n")] = '\0'; // Remove newline character

    printf("Input received: %s\n", input); // Debugging message

    // Convert operands to decimal
    convertOperands(input);

    // Debugging output: print the converted input
    printf("Converted input: %s\n", input);

    // Prompt user to enter the result types
    printf("Enter the result types (b for binary, d for decimal, h for hexadecimal): ");
    if (fgets(resultTypes, MAX, stdin) == NULL)
    {
        fprintf(stderr, "Failed to read result types\n");
        freeStack(&stack);
        return EXIT_FAILURE;
    }
    resultTypes[strcspn(resultTypes, "\n")] = '\0';

    printf("Result types received: %s\n", resultTypes); // Debugging message

    // Convert infix expression to postfix expression
    if (infixToPostfix(input, postfix) != 0)
    {
        fprintf(stderr, "Failed to convert infix to postfix\n");
        freeStack(&stack);
        return EXIT_FAILURE;
    }

    // Debugging output: print the postfix expression
    printf("Postfix expression: %s\n", postfix);

    // Evaluate the postfix expression
    Complex resultValue = evaluatePostfix(postfix);

    // Debugging output: print the result value
    printf("Result value: %.2f + %.2fi\n", resultValue.real, resultValue.imag);

    // Convert and print the result in each of the specified formats
    token = strtok(resultTypes, " ");
    while (token != NULL)
    {
        char type = token[0];
        switch (type)
        {
        case 'b':
            if (decimalToBinary((int)resultValue.real, result) != 0)
            {
                fprintf(stderr, "Failed to convert decimal to binary\n");
                freeStack(&stack);
                return EXIT_FAILURE;
            }
            printf("Result (binary): %s\n", result);
            break;
        case 'd':
            printf("Result (decimal): %.2f + %.2fi\n", resultValue.real, resultValue.imag);
            break;
        case 'h':
            if (decimalToHexadecimal((int)resultValue.real, result) != 0)
            {
                fprintf(stderr, "Failed to convert decimal to hexadecimal\n");
                freeStack(&stack);
                return EXIT_FAILURE;
            }
            printf("Result (hexadecimal): %s\n", result);
            break;
        default:
            fprintf(stderr, "Invalid result type\n");
            freeStack(&stack);
            return EXIT_FAILURE;
        }
        token = strtok(NULL, " ");
    }

    freeStack(&stack);
    return 0;
}

void convertOperands(char *input)
{
    char *token = strtok(input, " ");
    while (token != NULL)
    {
        int decimal;
        if (convertToDecimal(token, &decimal) == 0)
        {
            sprintf(token, "%d", decimal);
        }
        token = strtok(NULL, " ");
    }
}