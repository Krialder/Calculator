#include "error.h"
#include <stdio.h>
#include <stdlib.h>

static void handleError(const char *message) 
{
    fprintf(stderr, "Error: %s\n", message);
    exit(EXIT_FAILURE);
}
