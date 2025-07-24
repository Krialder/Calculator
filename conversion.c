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
            decimal += 1 << i; // Use bitwise shift for power of 2
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
            decimal += (digit - '0') * (1 << (4 * i)); // Use bitwise shift for power of 16
        }
        else if (digit >= 'A' && digit <= 'F')
        {
            decimal += (digit - 'A' + 10) * (1 << (4 * i)); 
        }
        else if (digit >= 'a' && digit <= 'f')
        {
            decimal += (digit - 'a' + 10) * (1 << (4 * i)); 
        }
    }
    return decimal;
}

// Function to convert a decimal number to a hexadecimal string
void decimalToHexadecimal(int decimal, char *hex)
{
    if (decimal == 0)
    {
        hex[0] = '0';
        hex[1] = '\0';
        return;
    }

    if (decimal < 0)
    {
        decimal = -decimal;
    }

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

// Function to convert a decimal number to a negative binary string
void decimalToNegativeBinary(int decimal, char *binary);

void decimalToNegativeBinary(int decimal, char *binary)
{
    if (decimal < 0)
    {
        binary[0] = '-';
        decimalToBinary(-decimal, binary + 1);
    }
    else
    {
        decimalToBinary(decimal, binary);
    }
}

void decimalToNegativeHexadecimal(int decimal, char *hex)
{
    if (decimal < 0)
    {
        hex[0] = '-';
        decimalToHexadecimal(-decimal, hex + 1);
    }
    else
    {
        decimalToHexadecimal(decimal, hex);
    }
}

int octalToDecimal(const char *octal) {
    int decimal = 0;
    int length = strlen(octal);
    for (int i = 0; i < length; i++) {
        char digit = octal[length - i - 1];
        if (digit >= '0' && digit <= '7') {
            decimal += (digit - '0') * (int)pow(8, i);
        } else {
            return -1; // Invalid octal digit
        }
    }
    return decimal;
}