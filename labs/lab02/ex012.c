#include <stdio.h>

int main()
{
    int x = 0;
    int y = 0;
    scanf("%d", &x);
    scanf("%d", &y);
    if (x % y == 0) 
        printf("yes");
    else
        printf("no");
    return 0;
}
