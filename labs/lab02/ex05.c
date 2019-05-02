#include <stdio.h>

int main() 
{
    int N;
    int m;
    int h;

    scanf("%d", &N);

    h = N / 3600;
    N %= 3600;
    m = N / 60;
    N %= 60;

    printf("%02d:%02d:%02d\n", h, m, N);

    return 0;
}
