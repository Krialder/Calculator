#include "error.h"
#include <stdio.h>
#include <stdlib.h>

void handleError(const char *message) 
{
    fprintf(stderr, "Error: %s\n", message);
    exit(EXIT_FAILURE);
}
