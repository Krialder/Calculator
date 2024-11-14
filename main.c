#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "calculator.h"

int main()
{
    char infix[MAX], postfix[MAX];
    Stack stack;
    initStack(&stack, MAX);

    // Prompt user to enter an infix expression
    printf("Enter an infix expression: ");
    fgets(infix, MAX, stdin);

    // Remove newline character if present
    size_t len = strlen(infix);
    if (len > 0 && infix[len - 1] == '\n') {
        infix[len - 1] = '\0';
    }

    // Check for empty input
    if (infix[0] == '\0')
    {
        fprintf(stderr, "Error: Empty input\n");
        return EXIT_FAILURE;
    }

    // Check for invalid characters
    for (int i = 0; infix[i] != '\0'; i++)
    {
        if (!isValidCharacter(infix[i]))
        {
            fprintf(stderr, "Error: Invalid character '%c' in input\n", infix[i]);
            return EXIT_FAILURE;
        }
    }

    // Convert the infix expression to postfix expression
    infixToPostfix(infix, postfix);

    // Print the postfix expression
    printf("Postfix expression: %s\n", postfix);

    // Evaluate the postfix expression and print the result
    printf("Result: %lf\n", evaluatePostfix(postfix));

    return 0;
}