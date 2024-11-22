#include "utils.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Include string header

// Function to check if a character is valid for the calculator
int isValidCharacter(char ch)
{
    // Return 1 if the character is a digit, decimal point, operator, or parenthesis
    return isdigit(ch) || ch == '.' || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^' || ch == '(' || ch == ')' || ch == 's' || ch == 'l' || ch == 'S' || ch == 'C' || ch == 'T' || ch == ' ' || ch == 'e';
}

// Function to check if the input is a binary number
int isBinary(const char *input)
{
    for (int i = 0; input[i] != '\0'; i++)
    {
        if (input[i] != '0' && input[i] != '1')
        {
            return 0; // Return 0 if any character is not '0' or '1'
        }
    }
    return 1; // Return 1 if all characters are '0' or '1'
}

// Function to check if the input is a decimal number
int isDecimal(const char *input)
{
    for (int i = 0; input[i] != '\0'; i++)
    {
        if (!isdigit(input[i]))
        {
            return 0; // Return 0 if any character is not a digit
        }
    }
    return 1; 
}

// Function to check if the input is a hexadecimal number
int isHexadecimal(const char *input)
{
    for (int i = 0; input[i] != '\0'; i++)
    {
        if (!isxdigit(input[i]))
        {
            return 0; // Return 0 if any character is not a hexadecimal digit
        }
    }
    return 1; 
}

// Function to convert input to a decimal number
int convertToDecimal(const char *input, int *decimal)
{
    if (isBinary(input))
    {
        return binaryToDecimal(input, decimal); // Convert binary input to decimal
    }
    else if (isDecimal(input))
    {
        *decimal = atoi(input); // Convert decimal input to integer
        return 0;
    }
    else if (isHexadecimal(input))
    {
        return hexadecimalToDecimal(input, decimal); // Convert hexadecimal input to decimal
    }
    else
    {
        fprintf(stderr, "Error: Invalid input format\n");
        return -1;
    }
}

int binaryToDecimal(const char *input, int *decimal) {
    *decimal = 0;
    while (*input) {
        *decimal = (*decimal << 1) + (*input++ - '0');
    }
    return 0;
}

int hexadecimalToDecimal(const char *input, int *decimal) {
    *decimal = (int)strtol(input, NULL, 16);
    return 0;
}