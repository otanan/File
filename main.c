#include "file.h"

int main() {
    printf("\n");
    FILE *fp = fopen("input.txt", "r");

    char line[MAX_LINE_LENGTH];
    int returnValue;

    while( (returnValue = next(fp, line)) != 0) {
    	printf("Next return value: %d\n", returnValue);
    	printf("String read: %s\n", line);
	}

	printf("Next return value: %d\n", returnValue);

    fclose(fp);
    printf("\n");
    return 0;
}