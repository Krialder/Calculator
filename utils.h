#ifndef UTILS_H
#define UTILS_H

#include "config.h" // Include the configuration header file

// Function to check if a character is valid for the calculator
int isValidCharacter(char ch);

// Function to check if the input is a binary number
int isBinary(const char *input);

// Function to check if the input is a decimal number
int isDecimal(const char *input);

// Function to check if the input is a hexadecimal number
int isHexadecimal(const char *input);

// Function to convert input to a decimal number
int convertToDecimal(const char *input, int *decimal);

int binaryToDecimal(const char *input, int *decimal);
int hexadecimalToDecimal(const char *input, int *decimal);

#endif // UTILS_H