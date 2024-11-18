#ifndef OPERATOR_H
#define OPERATOR_H

int precedence(char op);
int isOperator(char ch);
int isRightAssociative(char op);
double applyOperation(double a, double b, char op);

#endif // OPERATOR_H
