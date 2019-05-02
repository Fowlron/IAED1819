#include <stdio.h>

int main()
{
    int N;
    int sum = 0;
    int c = 0;

    scanf("%d", &N);

    while (N > 0)
    {
        sum += N % 10;
        N /= 10;
        c++;
    }
    printf("%d\n%d\n", c, sum);
    return 0;
}
