#include <stdio.h>

int main()
{
    int x = 0;
    int y = 0;
    int z = 0;
    scanf("%d", &x);
    scanf("%d", &y);
    scanf("%d", &z);
    if (x > y && x > z)
    {
        printf("%d\n", x);
    }
    else if (y > x && y > z)
    {
        printf("%d\n", y);
    }
    else
    {
        printf("%d\n", z);
    }
    return 0;
}
