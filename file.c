/***********************Include***********************/
#include <stdlib.h>
#include <ctype.h>

#include "file.h"

int next(FILE *fp, char *line) {
    char current;
    int index = 0;

    //Ends at end of file, space, and newline to separate strings
    while((current = getc(fp)) != EOF && !isspace(current))
        line[index++] = current;

    //If we're at the end of the file, and there was nothing read before
    //the index will be 0, so we will be returning the flag for ending
    if(current == EOF && index == 0)
        return 0;
    //If the index was never incremented, but it's also not the end of the file
    //we must've read whitespace, call ourselves back to read again
    else if(index == 0)
        return next(fp, line);

    //Ends the string
    line[index++] = '\0';

    //If the string only consists of the terminating character or less
    //then you basically read nothing
    return index;
}

/***********************Getters***********************/
bool is_next_int(FILE *fp) {
    char line[MAX_LINE_LENGTH];
    int len;
    //Immediately returns false if at EOF
    if( (len = next(fp, line)) == 0)
        return false;

    //Rewind from before the number
    fseek(fp, -len, SEEK_CUR);

    //Initializes the index for the loop early to alter the starting point
    //Takes the sign into consideration
    int i = 0;
    if(line[i] == '-') {
        //Checks edge case where the string is just "-"
        if(len == 2)
            return false;

        i++;
    }
    //Go through the string and check if it's a number
    for(; i < (len - 1); i++) {
        //If there is a single entry that is not numeric, the string overall isn't a number
        //i.e. 74G823 is not a number
        if(!isdigit(line[i]))
            return false;
    
    }

    return true;
}

bool is_next_double(FILE *fp) {
    char line[MAX_LINE_LENGTH];
    int len;

    if( (len = next(fp, line)) == 0 )
        return false;

    //Rewind
    fseek(fp, -len, SEEK_CUR);
    //Parse string to check if it's a number
    //There should only be one decimal
    int decimal_count = 0;

    //Notice that this works similarly to is_next_int
    //and returns positively even if the next number is technically an int
    //which just means that if we expect a float, and get an int
    //we'll end up promoting it just as we would want
    int i = 0;
    if(line[i] == '-') {
        //Checks edge case where the string is just "-"
        if(len == 2)
            return false;

        i++;
    }

    for(; i < (len - 1); i++) {
        if(line[i] == '.') {
            //If there's two decimal points, it's not a float
            //or if the decimal is at the end of the number (i.e. 352. )
            if(++decimal_count > 1 || i == (len - 1))
                return false;
            
            //Continue the loop, since we don't want to check if it's a digit,
            //it clearly isn't, but it's still valid syntax
            continue;
        }
        //You're not a decimal point, and you're not a number
        //so you're not a valid float
        if(!isdigit(line[i]))
            return false;
        
    }

    return true;
}

int next_int(FILE *fp, int *ip) {
    if(!is_next_int(fp))
        return 0;

    char number_string[MAX_LINE_LENGTH];
    //Fills the string with the number read, to-be-parsed
    next(fp, number_string);
    //Converts the number to base 10 and stores it in the
    //number pointer passed in
    *ip = strtol(number_string, NULL, 10);

    //Success return value
    return 1;
}

int next_double(FILE *fp, double *dp) {
    if(!is_next_double(fp))
        return 0;

    char number_string[MAX_LINE_LENGTH];

    next(fp, number_string);

    *dp = strtod(number_string, NULL);

    //Success
    return 1;
}

int next_doubles(FILE *fp, int times, double *dp) {
    for(int i = 0; i < times; i++) {
        //If a single reading of next_double fails, the function fails as a whole
        if(!next_double(fp, (dp + i))) 
            return 0;
    }
    //Success
    return 1;
}

int remaining_line(FILE *fp, char *line) { return fgets(line, MAX_LINE_LENGTH, fp) != NULL; }