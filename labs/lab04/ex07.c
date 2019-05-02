#include <stdio.h>
#include <string.h>

#define DIM 80

void deleteCharAtIndex(char str[], int idx)
{
    int i;
    for (i = idx; i < DIM-1; i++)
        str[i] = str[i+1];
    str[DIM-1] = '\0';
}

void apagaCaracter(char s[], char c)
{
    int i = 0, len = strlen(s);
    while (i < len)
    {
        if (s[i] == c)
        {
            deleteCharAtIndex(s, i);
            len--;
            i--;
        }
        i++;
    }
}


int leLinha(char s[])
{
    int i;
    for (i = 0; s[i-1] != '\n'; i++)
        s[i] = getchar();
    for (i--; i < DIM; i++)
        s[i] = '\0';
    return i;
}


int main()
{
    char s[DIM], c;
    leLinha(s);
    c = getchar();
    apagaCaracter(s, c);
    printf("%s\n", s);
    return 0;
}
