#include <stdio.h>
#include <stdlib.h>
#include "calculator.h"

int main()
{
    char input[MAX];
    char inputType, conversionType;
    Stack stack;
    initStack(&stack, MAX);

    // Prompt user to enter the type of the input number
    printf("Enter the type of the input number (b for binary, d for decimal, h for hexadecimal): ");
    scanf(" %c", &inputType);

    // Prompt user to enter the input number
    printf("Enter the input number: ");
    scanf("%s", input);

    // Check for empty input
    if (input[0] == '\0')
    {
        fprintf(stderr, "Error: Empty input\n");
        return EXIT_FAILURE;
    }

    // Convert input to decimal based on the specified type
    int decimalValue;
    switch (inputType)
    {
        case 'b':
            if (!isBinary(input))
            {
                fprintf(stderr, "Error: Invalid binary input\n");
                return EXIT_FAILURE;
            }
            decimalValue = binaryToDecimal(input);
            break;
        case 'd':
            if (!isDecimal(input))
            {
                fprintf(stderr, "Error: Invalid decimal input\n");
                return EXIT_FAILURE;
            }
            decimalValue = atoi(input);
            break;
        case 'h':
            if (!isHexadecimal(input))
            {
                fprintf(stderr, "Error: Invalid hexadecimal input\n");
                return EXIT_FAILURE;
            }
            decimalValue = hexadecimalToDecimal(input);
            break;
        default:
            fprintf(stderr, "Error: Invalid input type\n");
            return EXIT_FAILURE;
    }
    printf("Decimal value: %d\n", decimalValue);

    // Prompt user to enter the conversion type
    printf("Enter the conversion type (b for binary, d for decimal, h for hexadecimal): ");
    scanf(" %c", &conversionType);

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