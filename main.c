#include <stdlib.h>
#include "file.h"


int main() {
    printf("\n");
    FILE *fp = fopen("input.txt", "r");
    char *line = malloc(MAX_LINE_LENGTH);
    int len;


    // while( fscanf(fp, "%s", line) != 0) {

    //     printf("String read: %s\n", line);

    //     if(getc(fp) == EOF) {
    //         printf("End of file reached.\n");
    //         break;
    //     } else
    //         fseek(fp, -1, SEEK_CUR);
    // }  

    // while( next(fp, line) != 0 ) {
    //     printf("String read: %s\n", line);
    // }

    while(is_next_double(fp)) {
        printf("Number read: %f\n", next_double(fp));
    }

    fclose(fp);
    printf("\n");
    return 0;
}