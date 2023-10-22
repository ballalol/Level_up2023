#include<stdio.h>

int main(void)
{
    int a, b=5, c;
    float x, y=-.5, z;
    printf("a=");
    scanf("%d", &a);
    x=c=a;
    printf("a=%d, c=%d, x=%f\n", a, c, x);
    a+=b;
    printf("a=%d\n", a);
    x+=b+a;
    printf("x=%f\n", x);
    b+=a--;
    printf("b=%d\n", b);
    x-=++c;
    printf("x=%f\n", x);
    c=a/b;
    printf("c=%4d\n", c);
    c=a%b;
    printf("c+%d\n", c);
    x=5.3; 
    y+=((--x-1)/x++);
    printf("x=%f\ty=%.2f\n\n x=%.0f\ty=%.0f\n", x-1, y, x, y-1);
    z=a/2;
    printf("z=%f\n", z);
    z=(float)a/2;
    printf("z=%f\n", z);
    y=x/2;
    printf("y=%f\n", y);
    y=(int)x/2;
    printf("y=%f\n", y);
    z=a%2-(x+b)/c+(x-y)/(a-1)+1/4*a-y++ + ++b/3.;
    printf("a=%d b=%d c=%d x=%f y=%f z=%f\n" ,a, b, c, x, y, z);
    return 0;
}
