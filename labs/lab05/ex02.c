#include <stdio.h>

typedef struct complex
{
    float real;
    float imag;
} Complex;

Complex readComplex()
{
    float real, imag;
    char sign, i;
    Complex n;
    scanf("%f%c%f%c", &real, &sign, &imag, &i);
    n.real = real;
    if (sign == '-')
        imag *= -1;
    n.imag = imag;
    return n;
}

Complex sumComplex(Complex x, Complex y)
{
    Complex s;
    s.real = x.real + y.real;
    s.imag = x.imag + y.imag;
    return s;
}

int main()
{
    Complex x = readComplex();
    Complex y = readComplex();
    Complex s = sumComplex(x, y);
    printf("%.2f%c%.2fi", s.real, s.imag >= 0 ? '+' : '-', s.imag < 0 ? s.imag*-1 : s.imag);
    return 0;
}
