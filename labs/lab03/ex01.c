#include <stdio.h>

void quadrado(int N)
{
    int row, col;
    for (row = 0; row < N; row++)
    {
        for (col = 0; col < N; col++)
        {
            printf("%d\t", row+col+1);
        }
        printf("\n");
    }
}

int main()
{
    int N;
    scanf("%d", &N);

    quadrado(N);

    return 0;
}

int test()
{
    return 0;
}
