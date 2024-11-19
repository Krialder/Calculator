#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "calculator.h"
#include "conversion.h"
#include "stack.h"
#include "operator.h"
#include "operand.h"
#include "expression_conversion.h"
#include "common.h" // Include common.h
#include "declarations.h" // Include declarations.h

#define MAX 100

void printConversionSteps(int value);

int validateInput(const char *input, const char *resultTypes, const char *infix) {
    if (strlen(input) == 0) {
        HANDLE_ERROR("Input cannot be empty", 0);
        return 0;
    }
    if (strlen(resultTypes) == 0) {
        HANDLE_ERROR("Result types cannot be empty", 0);
        return 0;
    }
    for (int i = 0; i < strlen(infix); i++) {
        if (!strchr("+-*/^() ", infix[i]) && !isdigit(infix[i]) && !isxdigit(infix[i])) {
            HANDLE_ERROR("Invalid character in infix expression", 0);
            return 0;
        }
    }
    return 1;
}

int main() {
    char input[MAX];
    char resultTypes[MAX];
    char infix[MAX] = "";
    char postfix[MAX];
    Stack stack;
    initStack(&stack, MAX);
    double decimalValues[MAX];
    int invalidAttempts = 0; // Track invalid attempts
    char result[MAX]; // Declare result variable

    while (1) {
        printf("Enter the numbers with their types (e.g., b1010 d5 hA): ");
        fgets(input, MAX, stdin);
        input[strcspn(input, "\n")] = '\0';

        printf("Enter the operators in the order they will be used (+, -, *, /, ^): ");
        fgets(infix + strlen(infix), MAX - strlen(infix), stdin);
        infix[strcspn(infix, "\n")] = '\0'; // Corrected string termination

        printf("Enter the result types separated by spaces (b for binary, d for decimal, h for hexadecimal): ");
        fgets(resultTypes, MAX, stdin);
        resultTypes[strcspn(resultTypes, "\n")] = '\0';

        if (!validateInput(input, resultTypes, infix)) {
            invalidAttempts++;
            if (invalidAttempts >= 3) { // Break after 3 invalid attempts
                printf("Too many invalid attempts. Exiting...\n");
                break;
            }
            continue; // Retry on invalid input
        }

        invalidAttempts = 0; // Reset invalid attempts on valid input

        char *token = strtok(input, " ");
        int numCount = 0;
        while (token != NULL) {
            char type = token[0];
            char *value = token + 1;
            switch (type) {
                case 'b':
                case 'd':
                case 'h':
                    decimalValues[numCount++] = convertToDecimal(value);
                    break;
                default:
                    HANDLE_ERROR("Invalid input type", 0);
                    continue; // Retry on invalid input type
            }
            token = strtok(NULL, " ");
        }

        int valueIndex = 0;
        char infixExpression[MAX] = "";
        for (int i = 0; i < strlen(infix); i++) {
            if (strchr("+-*/^()", infix[i])) {
                if (i == 0 || strchr("+-*/^(", infix[i - 1])) {
                    strncat(infixExpression, &infix[i], 1);
                } else {
                    char buffer[20];
                    snprintf(buffer, sizeof(buffer), "%lf ", decimalValues[valueIndex++]);
                    strcat(infixExpression, buffer);
                    strncat(infixExpression, &infix[i], 1);
                    strcat(infixExpression, " ");
                }
            } else if (isspace(infix[i])) {
                continue;
            } else {
                HANDLE_ERROR("Invalid character in infix expression", 0);
                break; // Exit loop on invalid character in infix expression
            }
        }

        while (valueIndex < numCount) {
            char buffer[20];
            snprintf(buffer, sizeof(buffer), "%lf ", decimalValues[valueIndex++]);
            strcat(infixExpression, buffer);
        }

        infixToPostfix(infixExpression, postfix);

        printf("Postfix expression: %s\n", postfix);

        double resultValue = evaluatePostfix(postfix);

        token = strtok(resultTypes, " ");
        while (token != NULL) {
            char type = token[0];
            switch (type) {
                case 'b':
                    if (resultValue < 0) {
                        decimalToNegativeBinary((int)resultValue, result);
                        printConversionSteps((int)resultValue);
                        printf("Result (binary): -%s\n", result);
                    } else {
                        decimalToBinary((int)resultValue, result);
                        printf("Result (binary): %s\n", result);
                    }
                    break;
                case 'd':
                    printf("Result (decimal): %.2f\n", resultValue);
                    break;
                case 'h':
                    if (resultValue < 0) {
                        decimalToNegativeHexadecimal((int)resultValue, result);
                        printConversionSteps((int)resultValue);
                    } else {
                        decimalToHexadecimal((int)resultValue, result);
                    }
                    printf("Result (hexadecimal): %s\n", result);
                    break;
                default:
                    HANDLE_ERROR("Invalid result type", 0);
                    break;
            }
            token = strtok(NULL, " ");
        }
    }

    return 0;
}

void printConversionSteps(int value) {
    char result[MAX]; // Declare result variable within the function scope
    printf("Conversion steps for %d:\n", value);
    if (value < 0) {
        value = -value; // Converting the absolute value without context
        printf("Negative value detected. Converting the absolute value.\n");
    }
    printf("Binary: ");
    decimalToBinary(value, result);
    printf("%s\n", result);
    printf("Hexadecimal: ");
    decimalToHexadecimal(value, result);
    printf("%s\n", result);
}