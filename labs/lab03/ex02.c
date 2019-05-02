#include <stdio.h>

void piramide(int N)
{
    int row, c, space;
    for (row = 0; row < N; row++)
    {
        for (space = 2; space < (N - row)*2; space++)
        {
            printf(" ");
        }
        for (c = 0; c < row; c++)
        {
            printf("%d ", c+1);
        }

        for (c = row-1; c > 0; c--)
        {
            printf("%d ", c);
        }
        printf("\n");
    }
}


int main()
{
    int N;
    scanf("%d", &N);

    piramide(N+1);

    return 0;
}
