#include <stdio.h>

void cruz(int N)
{
    int row, col;
    for (row = 0; row < N; row++)
    {
        for (col = 0; col < N; col++)
        {
            if (row == col || row+1==N-col)
            {
                printf("* ");
            }
            else
            {
                printf("- ");
            }
        }
        printf("\n");
    }
}

int main()
{
    int N;
    scanf("%d", &N);

    cruz(N);

    return 0;
}
