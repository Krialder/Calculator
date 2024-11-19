#ifndef CONVERSION_H
#define CONVERSION_H

int binaryToDecimal(const char *binary);
void decimalToBinary(int decimal, char *binary);
int hexadecimalToDecimal(const char *hex);
void decimalToHexadecimal(int decimal, char *hex);
void decimalToNegativeBinary(int decimal, char *binary);
void decimalToNegativeHexadecimal(int decimal, char *hex);
int isBinary(const char *value);
int isNegativeBinary(const char *value);
int isDecimal(const char *value);
int isHexadecimal(const char *value);
int isNegativeHexadecimal(const char *value);
double convertToDecimal(const char *value);
void handlePostfixOperand(const char *operand, double *stack, int *top);

#endif // CONVERSION_H