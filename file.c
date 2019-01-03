/*
*Filename:      file.c
*Author:        Jonathan Delgado
*Description:   File IO wrapper to make file reading more intuitive in C.
*/

/***********************Include***********************/
//For string converters (strtol etc.)
#include <stdlib.h>
//For strlen
#include <string.h>
//For testing overflow (underflow) when casting longs to ints
#include <limits.h>

#include "file.h"

int next(FILE *fp, char *string) {
    //If the next character is EOF, signal the end
    if(getc(fp) == EOF)
        return EOF;
    //Rewind after having read the previous character to check for EOF
    fseek(fp, -1, SEEK_CUR);

    fscanf(fp, "%s", string);
    return strlen(string);
}

/***********************Getters***********************/
bool is_next_long(FILE *fp) {
    int len;
    char string[MAX_LINE_LENGTH];

    if( (len = next(fp, string)) == EOF) {
        printf("EOF, no next long.\n");
        return false;
    }
    fseek(fp, -len, SEEK_CUR);
    
    char *end_of_number;
    strtol(string, &end_of_number, 10);

    return end_of_number[0] == '\0';
}

bool is_next_int(FILE *fp) {
    //If there's no next long, then there definitely won't be an integer
    //also handles checking for EOF
    if(!is_next_long(fp))
        return false;

    char string[MAX_LINE_LENGTH];
    int len = next(fp, string);
    fseek(fp, -len, SEEK_CUR);

    long number = strtol(string, NULL, 10);
    //Effectively checks whether casting the long read would lead to overflow (underflow)
    //and if it doesn't, then simply cast the result in next_int
    return (number < 0 && number > INT_MIN)
        || (number > 0 && number < INT_MAX);
}

bool is_next_double(FILE *fp) {
    int len;
    char string[MAX_LINE_LENGTH];

    if( (len = next(fp, string)) == EOF) {
        printf("EOF, no next double.\n");
        return false;
    }
    fseek(fp, -len, SEEK_CUR);

    char *end_of_number;
    strtod(string, &end_of_number);

    return end_of_number[0] == '\0';
}

long next_long(FILE *fp) {
    if(!is_next_long(fp)) {
        printf(
            "Next string is not of type long.
             Please check for proper input.\n"
        );
        printf("Returning 0.\n");
        return 0;
    }
    char string[MAX_LINE_LENGTH];
    //is_next_long checks for EOF, so we can be confident in next working properly
    next(fp, string);
    //Since we are confident that the next entry is a number
    //we can pass NULL into the endptr argument
    return strtol(string, NULL, 10);
}

int next_int(FILE *fp) {
    if(!is_next_int(fp)) {
        printf("Next string is not of type int. Please check for proper input.\n");
        printf("Returning 0.\n");
        return 0;
    }

    return (int)next_long(fp);
}

double next_double(FILE *fp) {
    if(!is_next_double(fp)) {
        printf("Next string is not of type double. Please check for proper input.\n");
        printf("Returning 0.\n");
        return 0;
    }
    char string[MAX_LINE_LENGTH];
    next(fp, string);

    return strtod(string, NULL);
}

int next_doubles(FILE *fp, double *dp, int times) {
    for(int i = 0; i < times; i++) {
        //If 
        if(!is_next_double(fp)) {
            printf("next_doubles failed on count: %d/%d.\n", i, times);
            return 0;
        }
        *(dp + i) = next_double(fp);
    }
    //Success
    return 1;
}

int remaining_line(FILE *fp, char *line) {
    return fgets(line, MAX_LINE_LENGTH, fp) != NULL;
}

void skip_line(FILE *fp) {
    char line[MAX_LINE_LENGTH];
    remaining_line(fp, line);
}