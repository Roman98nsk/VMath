#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double f(double x, double y)
{
    return x + y;
}

void method_Runge_Kutta(double a, double b, double step)
{
    int points = (b - a) / step;
    double* array_X = malloc(sizeof(double) * points + 1);
    double n = a;
    for (int i = 0; i < points + 1; ++i) {
        array_X[i] = n;
        n += step;
    }
    double y = 1, k1, k2, k3, k4, Dy;
    for (int i = 0; i < points; ++i) {
        k1 = step * f(array_X[i], y);
        k2 = step * f(array_X[i] + step / 2, y + k1 / 2);
        k3 = step * f(array_X[i] + step / 2, y + k2 / 2);
        k4 = step * f(array_X[i] + step, y + k3);
        Dy = (k1 + 2 * k2 + 2 * k3 + k4) / 6;
        y = y + Dy;
    }
    printf("Метод Рунге-Кутта = %.4lf\n", y);
}

int main()
{
    int a = 0;
    int b = 10;
    double step = 0.001;
    method_Runge_Kutta(a, b, step);

    return 0;
}
