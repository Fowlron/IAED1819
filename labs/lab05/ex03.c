#include <stdio.h>
#include <string.h>

#define DIM 10

typedef struct stock
{
    char name[DIM];
    float value;
    float roi;
} Stock;

int main()
{
    Stock port[1000];
    int n, i, portSize = 0, highest_i = 0;
    float value, roi, highest_roi = 0;
    char name[DIM];
    Stock s;

    scanf("%d", &n);

    for (i = 0; i < n; i++)
    {
        scanf("%s %f %f", name, &value, &roi);
        strncpy(s.name, name, DIM);
        s.value = value;
        s.roi = roi;
        port[i] = s;
        portSize++;
    }

    for (i = 0; i < portSize; i++)
    {
        if (port[i].roi > highest_roi)
        {
            highest_i = i;
            highest_roi = port[i].roi;
        }
    }
    printf("%s %.2f %.2f\n", port[highest_i].name, port[highest_i].value, port[highest_i].roi);

    return 0;
}
