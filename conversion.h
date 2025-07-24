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

// Function to convert a decimal number to a negative binary string
void decimalToNegativeBinary(int decimal, char *binary);

// Function to convert a decimal number to a negative hexadecimal string
void decimalToNegativeHexadecimal(int decimal, char *hex);

int octalToDecimal(const char *octal);

#endif // CONVERSION_H