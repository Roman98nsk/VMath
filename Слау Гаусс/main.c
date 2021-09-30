#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void rsly_gauss(double** matrix, double* vector, int n)
{
    int index_row, index_col, k;
    double temp;
    /********** Прямой ход **********/
    for (k = 0; k < n; k++) {
        temp = 1 / matrix[k][k]; // для получения единицы на диагонали
        for (index_row = k; index_row < n; index_row++) {
            matrix[k][index_row] = matrix[k][index_row] * temp;
            // преобразуем строку (умножаем на обратное числу на диагонали)
        }
        vector[k] = vector[k] * temp;

        for (index_row = k + 1; index_row < n; index_row++) {
            for (index_col = k + 1; index_col < n; index_col++) {
                matrix[index_row][index_col] = matrix[index_row][index_col]
                        - matrix[index_row][k] * matrix[k][index_col];
            }
            vector[index_row]
                    = vector[index_row] - matrix[index_row][k] * vector[k];
        }
    }

    /********** Обратный ход **********/

    for (index_row = n - 2; index_row >= 0; index_row--) {
        for (index_col = index_row + 1; index_col < n; index_col++) {
            vector[index_row] = vector[index_row]
                    - matrix[index_row][index_col] * vector[index_col];
        }
    }
}

int main()
{
    printf("Введите кол-во переменных: ");
    int n;
    scanf("%d", &n);
    srand(time(NULL));
    double *matrix[n];
    for (int index_row = 0; index_row < n; index_row++) {
        matrix[index_row] = malloc(n * sizeof(double));
    }
    for (int index_row = 0; index_row < n; index_row++) {
        for (int index_col = 0; index_col < n; index_col++) {
            matrix[index_row][index_col] = rand() % 20 - 10;
        }
    }
    double* vector = malloc(sizeof(double) * n);
    for (int index_row = 0; index_row < n; index_row++) {
        vector[index_row] = rand() % 20 - 10;
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

    rsly_gauss(matrix, vector, n);

    printf("Решение, полученное методом Гаусса:\n");
    for (int index_row = 0; index_row < n; index_row++) {
        printf("X%d = %.2lf\n", index_row + 1, vector[index_row]);
    }
    return 0;
}
