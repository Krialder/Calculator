#include <stdio.h>
#include <stdlib.h>
#include "calculator.h"

int main()
{
    char input[MAX];
    char conversionType;
    Stack stack;
    initStack(&stack, MAX);

    // Prompt user to enter an expression (binary, decimal, or hexadecimal)
    printf("Enter an expression (binary, decimal, or hexadecimal): ");
    scanf("%s", input);

    // Prompt user to enter the conversion type
    printf("Enter the conversion type (b for binary, d for decimal, h for hexadecimal): ");
    scanf(" %c", &conversionType);

    // Check for empty input
    if (input[0] == '\0')
    {
        fprintf(stderr, "Error: Empty input\n");
        return EXIT_FAILURE;
    }

    // Convert input to decimal
    int decimalValue = convertToDecimal(input);
    printf("Decimal value: %d\n", decimalValue);

    // Convert decimal to the specified format
    char result[MAX];
    switch (conversionType)
    {
        case 'b':
            decimalToBinary(decimalValue, result);
            printf("Binary value: %s\n", result);
            break;
        case 'd':
            printf("Decimal value: %d\n", decimalValue);
            break;
        case 'h':
            decimalToHexadecimal(decimalValue, result);
            printf("Hexadecimal value: %s\n", result);
            break;
        default:
            fprintf(stderr, "Error: Invalid conversion type\n");
            return EXIT_FAILURE;
    }

    return 0;
}