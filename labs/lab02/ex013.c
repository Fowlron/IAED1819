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
        if (y > z)
            printf("%d %d %d\n", z, y, x);
        else
            printf("%d %d %d\n", y, z, x);
    }
    else if (y > x && y > z)
    {
        if (x > z)
            printf("%d %d %d\n", z, x, y);
        else
            printf("%d %d %d\n", x, z, y);
    }
    else
    {
        if (x > y)
            printf("%d %d %d\n", y, x, z);
        else
            printf("%d %d %d\n", x, y, z);
    }
    return 0;
}
