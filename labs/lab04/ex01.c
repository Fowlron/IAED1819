#include <stdio.h>
#include <stdlib.h>

int main()
{
    int len = 0;
    int tmp = 0;
    int o = 0;
    int i;
    int *ar;
    scanf("%d", &len);
    ar = malloc(sizeof(int)*len);
    for (i = 0; i < len; i++)
    {
        scanf("%d", &tmp);
        *(ar+i) = tmp;
    }
    for (i = 0; i < len; i++)
    {
        for (o = 0; o < *(ar+i); o++)
        {
            printf("*");
        }
        printf("\n");
    }
    return 0;

}
