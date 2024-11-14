#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "conversion.h"

// Function to convert a binary string to a decimal number
int binaryToDecimal(const char *binary)
{
    int decimal = 0;
    int length = strlen(binary);
    for (int i = 0; i < length; i++)
    {
        if (binary[length - i - 1] == '1')
        {
            decimal += pow(2, i); // Add the value of the current bit to the decimal result
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
        binary[index++] = (decimal % 2) + '0'; // Get the remainder when divided by 2 and convert it to a character
        decimal /= 2; // Divide the decimal number by 2
    }
    binary[index] = '\0';
    // Reverse the binary string to get the correct order
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
            decimal += (digit - '0') * pow(16, i); // Convert the digit to its decimal value and add it to the result
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
            hex[index++] = remainder + '0'; // Convert the remainder to a character
        }
        else
        {
            hex[index++] = remainder - 10 + 'A'; 
        }
        decimal /= 16; // Divide the decimal number by 16
    }
    hex[index] = '\0';
    // Reverse the hexadecimal string to get the correct order
    for (int i = 0; i < index / 2; i++)
    {
        char temp = hex[i];
        hex[i] = hex[index - i - 1];
        hex[index - i - 1] = temp;
    }
}