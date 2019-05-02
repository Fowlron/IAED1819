#include <stdio.h>
#include <stdlib.h>

int main() {
    char * s = malloc(sizeof(char) * 81);
    scanf("%s", s);

    do {
        printf("%s\n", s);
    } while ((++s)[0] != '\0');

    return 0;
}