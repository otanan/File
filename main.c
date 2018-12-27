#include "file.h"

//Do checks on next for EOF

int main() {
    printf("\n");
    FILE *fp = fopen("input.txt", "r");

    char line[MAX_LINE_LENGTH];
    int return_value;

    while( (return_value = next(fp, line)) != 0) {
    	printf("Next return value: %d\n", return_value);
    	printf("String read: %s\n", line);
	}

	printf("Next return value: %d\n", return_value);

    fclose(fp);
    printf("\n");
    return 0;
}