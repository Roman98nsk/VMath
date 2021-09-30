#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double f(double x)
{
    return -0.3 * pow(x, 3) + 4.2 * pow(x, 2) - 1.8 * x - 6.3;
}

double method_rectangle(double a, double b, int points)
{
    double width = (b - a) / points;
    double* array_X = malloc(sizeof(double) * points + 1);
    double h = a;
    for (int i = 0; i < points + 1; ++i) {
        array_X[i] = h;
        h += width;
    }
    double* array_X_2 = malloc(sizeof(double) * points);
    for (int i = 0; i < points; ++i) {
        array_X_2[i] = (array_X[i + 1] + array_X[i]) / 2;
    }
    double* array_Y = malloc(sizeof(double) * points);
    for (int i = 0; i < points; ++i) {
        array_Y[i] = f(array_X_2[i]);
    }
    double S = 0;
    for (int i = 0; i < points; ++i) {
        S += array_Y[i];
    }
    S *= width;

    return S;
}

double method_trapezium(double a, double b, int points)
{
    double width = (b - a) / points;
    double* array_X = malloc(sizeof(double) * points + 1);
    double h = a;
    for (int i = 0; i < points + 1; ++i) {
        array_X[i] = h;
        h += width;
    }
    double S = 0;
    for (int i = 0; i < points; ++i) {
        S += (f(array_X[i]) + f(array_X[i + 1])) / 2 * width;
    }

    return S;
}

double method_parabola(double a, double b, int points)
{
    double width = (b - a) / points;
    double S = f(a) + f(b);
    int k;
    for (int i = 1; i < points; ++i) {
        k = 2 + 2 * (i % 2);
        S += k * f(a + i * width);
    }
    S *= width / 3;

    return S;
}

int main()
{
    double a = 0;
    double b = 1;

    double S1, S2, S3;
    printf("Метод прямоугольников: ");
    S1 = method_rectangle(a, b, 5);
    printf("Ответ: %.3lf\n", S1);

    printf("Метод трапеций: ");
    S2 = method_trapezium(a, b, 5);
    printf("Ответ: %.3lf\n", S2);

    printf("Метод Парабол: ");
    S3 = method_parabola(a, b, 4);
    printf("Ответ: %.3lf\n", S3);

    return 0;
}