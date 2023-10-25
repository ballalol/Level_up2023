#include <math.h>
#include <stdio.h>

//  Написать программу, определяющую, площадь какой фигуры больше: круга радиуса R,
//  равностороннего треугольника с длиной стороны а или квадрата со стороной d. (используя ?:).

int main()
{
    int R = 15;
    int a = 15;
    int d = 15;
    double CircleS;
    double SquareS;
    double TriangleS;
    char LS;
    printf("R = %d is a radius of circle.\n", R);
    printf("a = %d is one of side of equilateral triangle.\n", a);
    printf("d = %d is one of side of square.\n", d);
    printf("The area of which shape is largest?\n");
    CircleS = M_PI * pow(R, 2);
    SquareS = pow(d, 2);
    TriangleS = sqrt(3) / 4 * pow(a, 2);
    printf("Circle = %f\n", CircleS);
    printf("Square = %f\n", SquareS);
    printf("Trianle = %f\n", TriangleS);
    LS = CircleS > TriangleS
                  ? CircleS > SquareS
                  :CircleS;
          TriangleS > CircleS
                  ? TriangleS > SquareS
                  : TriangleS;
          SquareS > CircleS
                  ? SquareS > TriangleS
                  : SquareS;
    printf("The area of %d is the largest.\n", LS);


    return 0;
}
