#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void L(double* array_l, double* array_Y_coord, int n)
{
    double L = 0;
    for (int i = 0; i < n; ++i) {
        L += array_Y_coord[i] * array_l[i];
    }
    printf("%.2lf\n\n", L);
}

void l(double* array_X_coord, double* array_Y_coord, double X, int n)
{
    double* array_l = malloc(sizeof(double) * n);
    for (int i = 0; i < n; ++i) {
        array_l[i] = 1;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j == i)
                continue;
            array_l[i]
                    *= ((X - array_X_coord[j])
                        / (array_X_coord[i] - array_X_coord[j]));
        }
        printf("l(%d) = %.2lf\n", i, array_l[i]);
    }
    printf("Значение интерполяционного полинома Лагранжа в точке X = %.2lf: ",
           X);
    L(array_l, array_Y_coord, n);
}

int main()
{
    printf("Введите кол-во точек: \n");
    int quantity_points;
    scanf("%d", &quantity_points);
    double X = 7.0;
    double* array_X_coord = malloc(sizeof(double) * quantity_points);
    double* array_Y_coord = malloc(sizeof(double) * quantity_points);
    for (int i = 0; i < quantity_points; ++i) {
        array_X_coord[i] = i;
        array_Y_coord[i] = rand() % 20 - 10;
        printf("Точка А(%d) = (%.2lf, %.2lf)\n",
               i,
               array_X_coord[i],
               array_Y_coord[i]);
    }
    l(array_X_coord, array_Y_coord, X, quantity_points);

    return 0;
}