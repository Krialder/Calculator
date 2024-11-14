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
            decimal += pow(2, i);
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
        binary[index++] = (decimal % 2) + '0';
        decimal /= 2;
    }
    binary[index] = '\0';
    // Reverse the binary string
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
            decimal += (digit - '0') * pow(16, i);
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
            hex[index++] = remainder + '0';
        }
        else
        {
            hex[index++] = remainder - 10 + 'A';
        }
        decimal /= 16;
    }
    hex[index] = '\0';
    // Reverse the hexadecimal string
    for (int i = 0; i < index / 2; i++)
    {
        char temp = hex[i];
        hex[i] = hex[index - i - 1];
        hex[index - i - 1] = temp;
    }
}