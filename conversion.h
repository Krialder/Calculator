#ifndef CONVERSION_H
#define CONVERSION_H

// Function to convert a binary string to a decimal number
int binaryToDecimal(const char *binary);

// Function to convert a decimal number to a binary string
void decimalToBinary(int decimal, char *binary);

// Function to convert a hexadecimal string to a decimal number
int hexadecimalToDecimal(const char *hex);

// Function to convert a decimal number to a hexadecimal string
void decimalToHexadecimal(int decimal, char *hex);

#endif // CONVERSION_H