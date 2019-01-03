/*
*Filename: 		main.c
*Author: 		Jonathan Delgado
*Description: 	Main source of entry for debugging and test file IO
*/

#include <stdlib.h>
#include "file.h"


int main() {
    printf("\n");
    FILE *fp = fopen("input.txt", "r");
    char line[MAX_LINE_LENGTH];





    fclose(fp);
    printf("\n");
    return 0;
}