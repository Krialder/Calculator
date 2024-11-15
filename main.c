#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "calculator.h"
#include "conversion.h"
#include "stack.h"

#define MAX 100

int main()
{
    char input[MAX];
    char resultTypes[MAX];
    Stack stack;
    initStack(&stack, MAX);

    // Prompt user to enter the numbers with their types and operators
    printf("Enter the numbers with their types and operators (e.g., b1010 (+) d5 (-) hA): ");
    fgets(input, MAX, stdin);
    input[strcspn(input, "\n")] = '\0'; // Remove newline character

    // Prompt user to enter the result types
    printf("Enter the result types (b for binary, d for decimal, h for hexadecimal): ");
    fgets(resultTypes, MAX, stdin);
    resultTypes[strcspn(resultTypes, "\n")] = '\0'; 

    // Parse the input numbers and operators, and convert numbers to decimal
    char *token = strtok(input, " ");
    int decimalValues[MAX];
    char operators[MAX];
    int numCount = 0, opCount = 0;
    while (token != NULL)
    {
        if (isdigit(token[0]) || token[0] == 'b' || token[0] == 'd' || token[0] == 'h')
        {
            char type = token[0];
            char *value = token + 1;
            switch (type)
            {
                case 'b':
                    if (!isBinary(value))
                    {
                        fprintf(stderr, "Error: Invalid binary input\n");
                        return EXIT_FAILURE;
                    }
                    decimalValues[numCount++] = binaryToDecimal(value);
                    break;
                case 'd':
                    if (!isDecimal(value))
                    {
                        fprintf(stderr, "Error: Invalid decimal input\n");
                        return EXIT_FAILURE;
                    }
                    decimalValues[numCount++] = atoi(value);
                    break;
                case 'h':
                    if (!isHexadecimal(value))
                    {
                        fprintf(stderr, "Error: Invalid hexadecimal input\n");
                        return EXIT_FAILURE;
                    }
                    decimalValues[numCount++] = hexadecimalToDecimal(value);
                    break;
                default:
                    fprintf(stderr, "Error: Invalid input type\n");
                    return EXIT_FAILURE;
            }
        }
        else if (strchr("+-*/^", token[0]) != NULL)
        {
            operators[opCount++] = token[0];
        }
        else
        {
            fprintf(stderr, "Error: Invalid input format\n");
            return EXIT_FAILURE;
        }
        token = strtok(NULL, " ");
    }

    //When doing that "Die ausführung des Codes kann nicht forgesetzt werdej, da libisl-23.dll nicht gefunden wurde"

    // Perform the calculations
    double resultValue = decimalValues[0];
    for (int i = 0; i < opCount; i++)
    {
        char operator = operators[i];
        double nextValue = decimalValues[i + 1];
        switch (operator)
        {
            case '+': resultValue += nextValue; break;
            case '-': resultValue -= nextValue; break;
            case '*': resultValue *= nextValue; break;
            case '/':
                if (nextValue == 0)
                {
                    fprintf(stderr, "Error: Division by zero\n");
                    return EXIT_FAILURE;
                }
                resultValue /= nextValue;
                break;
            case '^': resultValue = pow(resultValue, nextValue); break;
            default:
                fprintf(stderr, "Error: Invalid operator\n");
                return EXIT_FAILURE;
        }
    }

    // Convert and print the result in each of the specified formats
    char result[MAX];
    token = strtok(resultTypes, " ");
    while (token != NULL)
    {
        char type = token[0];
        switch (type)
        {
            case 'b':
                decimalToBinary((int)resultValue, result);
                printf("Result (binary): %s\n", result);
                break;
            case 'd':
                printf("Result (decimal): %d\n", (int)resultValue);
                break;
            case 'h':
                decimalToHexadecimal((int)resultValue, result);
                printf("Result (hexadecimal): %s\n", result);
                break;
            default:
                fprintf(stderr, "Error: Invalid result type\n");
                return EXIT_FAILURE;
        }
        token = strtok(NULL, " ");
    }

    return 0;
}