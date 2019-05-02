#include <stdio.h>
#include <float.h>

int main()
{
    int N = 0;
    float maior = FLT_MIN;
    float menor = FLT_MAX;
    int i;
    float n;
    scanf("%d", &N);
    for (i = 0; i < N; i++)
    {
       scanf("%f", &n);
       if (n >= maior)
       {
           maior = n;
       }
       if (n <= menor)
       {
           menor = n;
       }
    }

    printf("min: %f, max: %f\n", menor, maior);
    return 0;
}
