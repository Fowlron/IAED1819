#include <stdio.h>
#include <string.h>

#define DIM 80

int leLinha(char s[])
{
    int i;
    for (i = 0; s[i-1] != ' ' && s[i-1] != EOF; i++)
        s[i] = getchar();
    for (i--; i < DIM; i++)
        s[i] = '\0';
    return i;
}

/* 
 * A function that compares two large numbers digit by digit, assuming they have the same number of digits
 * Returns 1 if the first number is larger, -1 if the second one is larger, 0 if they're equal. */
int compareBigNumbers(char n1[], char n2[])
{
    int i, len = strlen(n1);
    for (i = 0; i < len; i++)
    {
        if (n1[i] > n2[i])
            return 1;
        else if (n2[i] > n1[i])
            return -1;
    }
    return 0;
}


int main()
{
    char s1[DIM], s2[DIM];
    int comparison;
    leLinha(s1);
    leLinha(s2);
    comparison = compareBigNumbers(s1, s2);
    printf("%s\n", comparison == 1 ? s1 : s2);
    return 0;
}
