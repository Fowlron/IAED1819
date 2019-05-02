#include <stdio.h>
#include <stdlib.h>

int main()
{
    int len = 0;
    int n;
    int tmp = 0;
    int *ar;
    int row, col;
    int maxrow = 0;

    scanf("%d", &len);
    ar = malloc(sizeof(int)*len);

    for (n = 0; n < len; n++)
    {
        scanf("%d", &tmp);
        *(ar+n) = tmp;
        if (tmp > maxrow)
            maxrow = tmp;
    }

    for (row = 0; row < maxrow; row++)
    {
        for (col = 0; col < len; col++)
        {
            if (*(ar+col) > row)
                printf("*");
            else
                printf(" ");
        }
        printf("\n");
    }

    return 0;
}
