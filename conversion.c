#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "conversion.h"
#include "common.h" // Include common.h
#include "declarations.h" // Include declarations.h

#define STACK_SIZE 100 // Ensure STACK_SIZE is defined

int binaryToDecimal(const char *binary) {
    if (binary == NULL || *binary == '\0') {
        HANDLE_ERROR("Invalid binary input", 0);
        return 0;
    }
    int decimal = 0;
    int length = strlen(binary);
    int isNegative = binary[0] == '-';
    for (int i = isNegative ? 1 : 0; i < length; i++) {
        if (binary[length - i - 1] == '1') {
            decimal += 1 << i;
        } else if (binary[length - i - 1] != '0') {
            HANDLE_ERROR("Invalid binary number", 0);
            return 0;
        }
    }
    return isNegative ? -decimal : decimal;
}

void decimalToBinary(int decimal, char *binary) {
    if (decimal == 0) {
        strcpy(binary, "0");
        return;
    }

    int isNegative = decimal < 0;
    if (isNegative) {
        decimal = -decimal;
    }

    int index = 0;
    while (decimal > 0) {
        binary[index++] = (decimal % 2) + '0';
        decimal /= 2;
    }
    if (isNegative) {
        binary[index++] = '-';
    }
    binary[index] = '\0';

    // Reverse the string
    for (int i = 0; i < index / 2; i++) {
        char temp = binary[i];
        binary[i] = binary[index - i - 1];
        binary[index - i - 1] = temp;
    }
}

int hexadecimalToDecimal(const char *hex) {
    if (hex == NULL || *hex == '\0') {
        HANDLE_ERROR("Invalid hexadecimal input", 0);
        return 0;
    }
    int decimal = 0;
    int length = strlen(hex);
    int isNegative = hex[0] == '-';
    for (int i = isNegative ? 1 : 0; i < length; i++) {
        char digit = hex[length - i - 1];
        if (digit >= '0' && digit <= '9') {
            decimal += (digit - '0') * pow(16, i);
        } else if (digit >= 'A' && digit <= 'F') {
            decimal += (digit - 'A' + 10) * pow(16, i);
        } else if (digit >= 'a' && digit <= 'f') {
            decimal += (digit - 'a' + 10) * pow(16, i);
        } else {
            HANDLE_ERROR("Invalid hexadecimal number", 0);
            return 0;
        }
    }
    return isNegative ? -decimal : decimal;
}

void decimalToHexadecimal(int decimal, char *hex) {
    if (decimal == 0) {
        strcpy(hex, "0");
        return;
    }

    int isNegative = decimal < 0;
    if (isNegative) {
        decimal = -decimal;
    }

    int index = 0;
    while (decimal > 0) {
        int remainder = decimal % 16;
        if (remainder < 10) {
            hex[index++] = remainder + '0';
        } else {
            hex[index++] = remainder - 10 + 'A';
        }
        decimal /= 16;
    }
    if (isNegative) {
        hex[index++] = '-';
    }
    hex[index] = '\0';

    // Reverse the string
    for (int i = 0; i < index / 2; i++) {
        char temp = hex[i];
        hex[i] = hex[index - i - 1];
        hex[index - i - 1] = temp;
    }
}

double convertToDecimal(const char *value) {
    if (isBinary(value)) {
        return binaryToDecimal(value);
    } else if (isHexadecimal(value)) {
        return hexadecimalToDecimal(value);
    } else if (isDecimal(value)) {
        return atof(value);
    } else if (isNegativeBinary(value)) {
        return -binaryToDecimal(value + 1);
    } else if (isNegativeHexadecimal(value)) {
        return -hexadecimalToDecimal(value + 1);
    } else {
        HANDLE_ERROR("Invalid input format", 0);
        return 0;
    }
}

void decimalToNegativeBinary(int decimal, char *binary) {
    if (decimal >= 0) {
        HANDLE_ERROR("Input is not a negative decimal", 0);
        return;
    }
    decimalToBinary(-decimal, binary);
    char temp[100];
    strcpy(temp, binary);
    strcpy(binary, "-");
    strcat(binary, temp);
}

void decimalToNegativeHexadecimal(int decimal, char *hex) {
    if (decimal >= 0) {
        HANDLE_ERROR("Input is not a negative decimal", 0);
        return;
    }
    decimalToHexadecimal(-decimal, hex);
    char temp[100];
    strcpy(temp, hex);
    strcpy(hex, "-");
    strcat(hex, temp);
}

int isBinary(const char *value) {
    for (int i = 0; value[i] != '\0'; i++) {
        if (value[i] != '0' && value[i] != '1') {
            return 0;
        }
    }
    return 1;
}

int isNegativeBinary(const char *value) {
    return value[0] == '-' && isBinary(value + 1);
}

int isDecimal(const char *value) {
    for (int i = 0; value[i] != '\0'; i++) {
        if (!isdigit(value[i])) {
            return 0;
        }
    }
    return 1;
}

int isHexadecimal(const char *value) {
    for (int i = 0; value[i] != '\0'; i++) {
        if (!isxdigit(value[i])) {
            return 0;
        }
    }
    return 1;
}

int isNegativeHexadecimal(const char *value) {
    return value[0] == '-' && isHexadecimal(value + 1);
}

void handlePostfixOperand(const char *token, double *stack, int *top) {
    stack[++(*top)] = atof(token);
}