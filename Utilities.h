#ifndef UTILITIES_H
#define UTILITIES_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* read_line(FILE* location);
char** split_line(char *line);
int num_args(char** args);

#endif /* Utilities_h */
