#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "calculator.h"
#include "conversion.h"
#include "stack.h"
#include "operator.h"
#include "operand.h"
#include "expression_conversion.h"
#include "error.h"

#define MAX 100 // Define MAX constant

int main()
{
    char input[MAX];
    char resultTypes[MAX];
    char infix[MAX] = "";
    char postfix[MAX];
    Stack stack;
    initStack(&stack, MAX);

    // Prompt user to enter the numbers with their types
    printf("Enter the numbers with their types (e.g., b1010 d5 hA): ");
    fgets(input, MAX, stdin);
    input[strcspn(input, "\n")] = '\0'; // Remove newline character

    // Prompt user to enter the operators in the order they will be used in the expression
    printf("Enter the operators in the order they will be used (+, -, *, /, ^): ");
    fgets(infix + strlen(infix), MAX - strlen(infix), stdin);
    infix[strcspn(infix, "\n")] = '\0'; 

    // Prompt user to enter the result types
    printf("Enter the result types separated by spaces (b for binary, d for decimal, h for hexadecimal): ");
    fgets(resultTypes, MAX, stdin);
    resultTypes[strcspn(resultTypes, "\n")] = '\0'; 

    // Parse the input numbers and convert them to decimal
    char *token = strtok(input, " ");
    double decimalValues[MAX];
    int numCount = 0;
    while (token != NULL)
    {
        char type = token[0];
        char *value = token + 1;
        switch (type)
        {
            case 'b':
                if (!isBinary(value) && !isNegativeBinary(value))
                {
                    handleError("Invalid binary input");
                }
                decimalValues[numCount++] = convertToDecimal(value);
                break;
            case 'd':
                if (!isDecimal(value))
                {
                    handleError("Invalid decimal input");
                }
                decimalValues[numCount++] = atof(value);
                break;
            case 'h':
                if (!isHexadecimal(value) && !isNegativeHexadecimal(value))
                {
                    handleError("Invalid hexadecimal input");
                }
                decimalValues[numCount++] = convertToDecimal(value);
                break;
            default:
                handleError("Invalid input type");
        }
        token = strtok(NULL, " ");
    }

    // Construct the infix expression
    int valueIndex = 0;
    char infixExpression[MAX] = "";
    for (int i = 0; i < strlen(infix); i++)
    {
        if (strchr("+-*/^()", infix[i]))
        {
            if (i == 0 || strchr("+-*/^(", infix[i - 1]))
            {
                strncat(infixExpression, &infix[i], 1);
            }
            else
            {
                char buffer[20];
                snprintf(buffer, sizeof(buffer), "%lf", decimalValues[valueIndex++]);
                strcat(infixExpression, buffer);
                strncat(infixExpression, &infix[i], 1);
            }
        }
    }
    if (valueIndex < numCount) {
        char buffer[20];
        snprintf(buffer, sizeof(buffer), "%lf", decimalValues[valueIndex++]);
        strcat(infixExpression, buffer);
    }

    // Convert infix to postfix
    infixToPostfix(infixExpression, postfix);

    // Print the postfix expression for debugging
    printf("Postfix expression: %s\n", postfix);

    // Evaluate the postfix expression
    double resultValue = evaluatePostfix(postfix);

    // Convert and print the result in each of the specified formats
    char result[MAX];
    token = strtok(resultTypes, " ");
    while (token != NULL)
    {
        char type = token[0];
        switch (type)
        {
            case 'b':
                if (resultValue < 0)
                {
                    decimalToNegativeBinary((int)resultValue, result);
                    printConversionSteps((int)resultValue);
                    printf("Result (binary): -%s\n", result); // Adjust the binary output
                }
                else
                {
                    decimalToBinary((int)resultValue, result);
                    printf("Result (binary): %s\n", result);
                }
                break;
            case 'd':
                printf("Result (decimal): %.2f\n", resultValue);
                break;
            case 'h':
                if (resultValue < 0)
                {
                    decimalToNegativeHexadecimal((int)resultValue, result);
                    printConversionSteps((int)resultValue);
                }
                else
                {
                    decimalToHexadecimal((int)resultValue, result);
                }
                printf("Result (hexadecimal): %s\n", result);
                break;
            default:
                handleError("Invalid result type");
        }
        token = strtok(NULL, " ");
    }

    return 0;
}