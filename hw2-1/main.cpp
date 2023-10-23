#include <math.h>
#include <stdio.h>
int main (void)
{
    unsigned int x;
    double a;
    double b;

    printf("x = ");
    scanf("%d", &x);
    a = 2 * cos( x - (M_PI / 6 )) + sqrt (2);
    b = 1 / (2 * log(x)) + pow(sin(pow(x, 2)), 2);
    double Y = a / b * exp( 3 * x);
    printf("Y = %f", Y);
return 0;
}
