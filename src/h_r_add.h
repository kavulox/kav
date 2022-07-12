#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *r_vstr(const char *command)
{
    FILE *output = popen(command, "r");
    if (output == NULL)
    {
        return NULL;
    }
    else
    {
        char *returnOutput = malloc(256);
        const int scanf_return = fscanf(output, "%[^\n]256s", returnOutput);
        pclose(output);
        if (scanf_return == EOF)
        {
            fprintf(stderr, "Error: Scanf Failed sucks to be you");
            exit(EXIT_FAILURE);
        }
        else
        {
            return returnOutput;
        }
    }
}
