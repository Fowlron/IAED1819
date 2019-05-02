#include <stdio.h>

int main() 
{
    int N = 0;
    int div = 0;
    int i;

    scanf("%d", &N);

    for (i = 1; i < N/2+1; i++)
    {
        if (N % i == 0)
            div++;
    }
    printf("%d\n", div + 1);
    return 0;
}
