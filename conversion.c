#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "conversion.h"

// Function to convert a decimal number to a binary string
int decimalToBinary(int decimal, char *binary)
{
    int index = 0;
    if (decimal == 0)
    {
        binary[index++] = '0';
    }
    else
    {
        while (decimal > 0)
        {
            binary[index++] = (decimal % 2) + '0';
            decimal /= 2;
        }
    }
    binary[index] = '\0';
    // Reverse the binary string to get the correct order
    for (int i = 0; i < index / 2; i++)
    {
        char temp = binary[i];
        binary[i] = binary[index - i - 1];
        binary[index - i - 1] = temp;
    }
    return 0;
}

// Function to convert a decimal number to a hexadecimal string
int decimalToHexadecimal(int decimal, char *hex)
{
    int index = 0;
    if (decimal == 0)
    {
        hex[index++] = '0';
    }
    else
    {
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
    }
    hex[index] = '\0';
    // Reverse the hexadecimal string to get the correct order
    for (int i = 0; i < index / 2; i++)
    {
        char temp = hex[i];
        hex[i] = hex[index - i - 1];
        hex[index - i - 1] = temp;
    }
    return 0;
}