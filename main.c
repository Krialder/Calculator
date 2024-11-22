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

    // Evaluate the expression
    double resultValue = evaluateExpression(input);

    // Display the results in the specified formats
    displayResults(resultValue, resultTypes);

    freeStack(&stack);
    return 0;
}

void convertOperands(char *input)
{
    char converted[MAX] = "";
    char *token = strtok(input, " ");
    while (token != NULL)
    {
        if (isOperator(token[0]) && strlen(token) == 1) // Check if token is an operator
        {
            strcat(converted, token);
            strcat(converted, " ");
        }
        else if (isdigit(token[0]) || token[0] == 'b' || token[0] == 'd' || token[0] == 'h') // Check if token is a number with prefix
        {
            int decimal;
            if (convertToDecimal(token, &decimal) == 0)
            {
                char buffer[50];
                sprintf(buffer, "%d ", decimal);
                strcat(converted, buffer);
            }
            else
            {
                strcat(converted, token);
                strcat(converted, " ");
            }
        }
        else
        {
            strcat(converted, token);
            strcat(converted, " ");
        }
        token = strtok(NULL, " ");
    }
    converted[strlen(converted) - 1] = '\0'; // Remove the trailing space
    strcpy(input, converted);
}