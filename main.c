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
#include "print_conversion_steps.h"

#define MAX 100 // Define MAX constant

int main()
{
    char infix[MAX];
    char resultTypes[MAX];
    char postfix[MAX];
    Stack stack;
    initStack(&stack, MAX);

    while (1) {
        // Prompt user to enter the full infix expression with types and operators
        printf("Enter your infix expression using the following syntax:\n");
        printf("- Use b for binary, d for decimal, h for hexadecimal (e.g., b1010, d5, hA)\n");
        printf("- Supported operators: +  -  *  /  %%  ^\n");
        printf("- Use parentheses ( and ) for grouping and precedence\n");
        printf("- Type 'exit' to quit the program.\n");
        printf("Example: (h11 + d3) / b10\n");
        printf("Your expression: ");
        fgets(infix, MAX, stdin);
        infix[strcspn(infix, "\n")] = '\0';
        if (strcmp(infix, "exit") == 0) {
            printf("Exiting calculator. Goodbye!\n");
            break;
        }

        // Prompt user to enter the result types
        printf("Enter the result types separated by spaces (b for binary, d for decimal, h for hexadecimal): ");
        fgets(resultTypes, MAX, stdin);
        resultTypes[strcspn(resultTypes, "\n")] = '\0';

        // Parse the infix expression, convert operands to decimal, and build a new infix string
        char infixExpression[MAX] = "";
        char token[MAX];
        int i = 0, j = 0;
        while (infix[i] != '\0') {
            // Skip spaces
            if (infix[i] == ' ') { i++; continue; }
            // If operator or parenthesis
            if (strchr("+-*/^()", infix[i])) {
                size_t len = strlen(infixExpression);
                if (len > 0 && infixExpression[len-1] != ' ') {
                    strcat(infixExpression, " ");
                }
                strncat(infixExpression, &infix[i], 1);
                strcat(infixExpression, " ");
                i++;
                continue;
            }
            // If operand with type
            int k = 0;
            while (infix[i] != '\0' && infix[i] != ' ' && !strchr("+-*/^()", infix[i])) {
                token[k++] = infix[i++];
            }
            token[k] = '\0';
            if (k > 0) {
                char type = token[0];
                char *value = token + 1;
                double decimal = 0;
                switch (type) {
                    case 'b':
                        decimal = binaryToDecimal(value);
                        break;
                    case 'd':
                        decimal = atof(value);
                        break;
                    case 'h':
                        {
                            char hexBuffer[34];
                            snprintf(hexBuffer, sizeof(hexBuffer), "0x%s", value);
                            decimal = hexadecimalToDecimal(hexBuffer);
                        }
                        break;
                    default:
                        handleError("Invalid input type");
                }
                char buffer[32];
                if (decimal == (int)decimal) {
                    snprintf(buffer, sizeof(buffer), "%d", (int)decimal);
                } else {
                    snprintf(buffer, sizeof(buffer), "%.2f", decimal);
                }
                strcat(infixExpression, buffer);
                strcat(infixExpression, " ");
            }
        }

        // Print the constructed infix expression for debugging
        printf("Constructed infix expression: %s\n", infixExpression);

        // Convert infix to postfix
        infixToPostfix(infixExpression, postfix);
        postfix[strlen(postfix)] = '\0'; // Ensure null-termination

        // Print the postfix expression for debugging
        printf("Postfix expression: %s\n", postfix);

        // Evaluate the postfix expression and print a summary
        double resultValue = 0;
        int error = 0;
        printf("\n--- Calculation Result ---\n");
        resultValue = evaluatePostfix(postfix);
        printf("Final value: %.6f\n", resultValue);

        // Print all requested result types in a summary
        char result[MAX];
        char *typeToken = strtok(resultTypes, " ");
        while (typeToken != NULL)
        {
            char type = typeToken[0];
            switch (type)
            {
                case 'b':
                    if (resultValue < 0)
                    {
                        decimalToNegativeBinary((int)resultValue, result);
                        printConversionSteps((int)resultValue);
                        printf("Result (binary): -%s\n", result);
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
            typeToken = strtok(NULL, " ");
        }
        printf("-------------------------\n\n");
    }
    return 0;
}