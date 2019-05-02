#include <stdio.h>

int main()
{
    int N = 0;
    float n = 0;
    float avg = 0;
    int i;

    scanf("%d", &N);

    for (i = 0; i < N; i++)
    {
        scanf("%f", &n);
        avg += n;
    }
    avg /= N;
    printf("%.2f\n", avg);

    return 0;
}
