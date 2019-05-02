#include <stdio.h>

#define DIM 80

int leLinha(char s[])
{
    char c;
    int n = 0;
    while ((c = getchar()) != EOF && c != '\n')
    {
        s[n] = c;
        n++;
    }
    s[n] = '\0';
    return n;
}


int main()
{
    char s[DIM];
    int i, len = leLinha(s);
    for (i = 0; i < len; i++)
    {
        printf("%c", s[i]);
    }
    printf("\n");
    return 0;
}
