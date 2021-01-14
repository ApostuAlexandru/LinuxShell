#include "Utilities.h"

char* read_line(FILE* location) {

    char* line = NULL;
    size_t aux = 0;

    if ( getline(&line, &aux, location) == -1 )
      exit(EXIT_SUCCESS);
    // getline(&line, &aux, location);
    return line;
}

char** split_line(char *line) {

    int maxElements = 32, position = 0;

    char** array = malloc(maxElements * sizeof(char*));

    if (!array) {
        fprintf(stderr, "[Error] Bad alloc of array! \n");
        exit(EXIT_FAILURE);
    }

    char* element = strtok(line, " \t\r\n\a");
    while (element != NULL) {
        array[position] = element;
        position++;

        if (position >= maxElements) {
            maxElements += 32;
            array = realloc(array, maxElements * sizeof(char*));

            if (!array) {
                fprintf(stderr, "[Error] Bad realloc of array! \n");
                exit(EXIT_FAILURE);
            }
        }
        element = strtok(NULL, " \t\r\n\a");
    }

    array[position] = NULL;

    return array;
}

int num_args(char** args) {

    int nrcom = 0;
    char* elem = args[0];
    while(elem != NULL) nrcom++, elem = args[nrcom];

    return nrcom;
}
