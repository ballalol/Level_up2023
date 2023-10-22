#include <stdio.h>
int main (void)
{
    int a = 5;
    int c = 5;
    int b = 7;
    int d = 4;
   a = c;
   printf("a=%d\n, c=%d\n", a, c);
   a = a + b - 2;
   printf("a=%d\n, b=%d\n, c=%d\n, d=%d\n", a, b, c, d);
   c = c + 1, d = c - a + d;
   printf ("a=%d\n, b=%d\n, c=%d\n, d=%d\n", a, b, c, d);
   a = a * c, c = c - 1;
   printf("a=%d\n, b=%d\n, c=%d\n, d=%d\n", a, b, c, d);
   a = a / 10, c = c / 2, b = b - 1;
   printf ("a=%d\n, b=%d\n, c=%d\n, d=%d\n", a, b, c, d);
   d= d * (c + b + a);
   printf("d=%d\n, c=%d\n, b=%d\n, a=%d\n", d, c, b, a);
    return 0;
}
