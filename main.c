#include "file.h"

int main() {
    printf("\n");
    FILE *fp = fopen("input.txt", "r");
    char line[MAX_LINE_LENGTH];

    next(fp, line);
    printf("String read: %s\n", line);


    fclose(fp);
    printf("\n");
    return 0;
}