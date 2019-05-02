#include <stdio.h>
#include <string.h>

#define DIM 80

int isPalindrome(char word[], int len)
{
    int i;
    for (i = 0; i < len/2; i++)
    {
        if (word[i] != word[len-i-1])
            return 0;
    }
    return 1;
}


int main()
{
    char word[DIM];
    int len;
    scanf("%s", word);
    len = strlen(word);
    printf(isPalindrome(word, len) ? "yes\n" : "no\n");
    return 0;
}
