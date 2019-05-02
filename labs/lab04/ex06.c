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
    return n;
}

void maiusculas(char s[], int len)
{
    int i;
    for (i = 0; i < len; i++)
    {
        if (s[i] <= 'z' && s[i] >= 'a')
            s[i] += 'A' - 'a';
    }
}

int main()
{
    char s[DIM];
    int i, len = leLinha(s);
    maiusculas(s, len);
    for (i = 0; i < len; i++)
    {
        printf("%c", s[i]);
    }
    printf("\n");
    return 0;
}
