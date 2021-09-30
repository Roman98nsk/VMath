#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void simple_iteration_method(double** matrix, double* vector, int n)
{
    double eps = 0.01;
    double* roots = malloc(sizeof(double) * n);
    double* roots_prev = malloc(sizeof(double) * n);
    for (int i = 0; i < n; i++) {
        roots[i] = 0;
        roots_prev[i] = 0;
    }
    double delta;
    do {
        delta = 0;
        for (int i = 0; i < n; ++i) {
            double diff = 0;
            for (int j = 0; j < n; ++j) {
                if (j == i) {
                    continue;
                }
                diff -= matrix[i][j] * roots[j];
            }
            double prev = roots_prev[i];
            roots_prev[i] = (vector[i] + diff) / matrix[i][i];
            if (fabs(roots_prev[i] - prev) > delta) {
                delta = fabs(roots_prev[i] - prev);
            }
        }
        for (int i = 0; i < n; ++i) {
            roots[i] = roots_prev[i];
        }
    } while (delta > eps);
    for (int i = 0; i < n; ++i) {
        printf("X%d = %.2lf\n", i + 1, roots[i]);
    }
}

void Seidels_method(double** matrix, double* vector, int n)
{
    double eps = 0.01;
    double* roots = malloc(sizeof(double) * n);
    for (int index_row = 0; index_row < n; index_row++) {
        roots[index_row] = 0;
    }
    double delta;
    do {
        delta = 0;
        for (int i = 0; i < n; ++i) {
            double diff = 0;
            for (int j = 0; j < n; ++j) {
                if (j == i) {
                    continue;
                }
                diff -= matrix[i][j] * roots[j];
            }
            double prev = roots[i];
            roots[i] = (vector[i] + diff) / matrix[i][i];
            if (fabs(roots[i] - prev) > delta) {
                delta = fabs(roots[i] - prev);
            }
        }
    } while (delta > eps);
    for (int i = 0; i < n; ++i) {
        printf("X%d = %.2lf\n", i + 1, roots[i]);
    }
}

int convergence_condition(double** matrix, int n)
{
    double sum;
    for (int i = 0; i < n; ++i) {
        sum = 0;
        for (int j = 0; j < n; ++j) {
            if (j == i) {
                continue;
            }
            sum += fabs(matrix[i][j]);
        }
        if (fabs(matrix[i][i]) < sum) {
            printf("Условие сходимости не выполняется.\n");
            return -1;
        }
    }
    printf("Условие сходимости выполняется.\n");
    return 0;
}

int main()
{
    printf("Введите кол-во переменных: ");
    int n;
    scanf("%d", &n);
    srand(time(NULL));
    double *matrix[n], *matrix2[n];
    for (int index_row = 0; index_row < n; index_row++) {
        matrix[index_row] = malloc(n * sizeof(double));
        matrix2[index_row] = malloc(n * sizeof(double));
    }
    for (int index_row = 0; index_row < n; index_row++) {
        for (int index_col = 0; index_col < n; index_col++) {
            matrix[index_row][index_col] = rand() % 20 - 10;
            if (index_row == index_col) {
                matrix[index_row][index_col] = rand() % 30 + 20;
            }
            matrix2[index_row][index_col] = matrix[index_row][index_col];
        }
    }
    double* vector = malloc(sizeof(double) * n);
    double* vector2 = malloc(sizeof(double) * n);
    for (int index_row = 0; index_row < n; index_row++) {
        vector[index_row] = rand() % 20 - 10;
        vector2[index_row] = vector[index_row];
    }

    for (int index_row = 0; index_row < n; index_row++) {
        for (int index_col = 0; index_col < n + 1; index_col++) {
            if (index_col != n) {
                printf("%.0lf  ", matrix[index_row][index_col]);
            } else {
                printf("|  %.0lf  ", vector[index_row]);
            }
        }
        printf("\n");
    }

    double eps = 0.01;

    if (convergence_condition(matrix, n) == -1)
        return -1;

    printf("Метод простых итераций: \n");
    simple_iteration_method(matrix, vector, n);
    printf("Метод Зейделя: \n");
    Seidels_method(matrix, vector, n);

    return 0;
}