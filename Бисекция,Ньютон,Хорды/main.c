#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double f(double x)
{
    // double da = cos(2 / x) - 2 * sin(1 / x) + (1 / x);
    // printf("f(%.2lf) = %.4lf\n", x, da);
    return cos(2 / x) - 2 * sin(1 / x) + (1 / x);
}

double f_hatch(double x)
{
    return (2 * sin(2 / x)) / pow(x, 2) - (1 / pow(x, 2))
            + (2 * cos(1 / x)) / pow(x, 2);
}

double f_hatch_hatch(double x)
{
    return (2 / pow(x, 3)) - (4 * sin(2 / x)) / pow(x, 3)
            - (4 * cos(2 / x)) / pow(x, 4) - (4 * cos(1 / x)) / pow(x, 3)
            + (2 * sin(1 / x)) / pow(x, 4);
}

int convergence_condition(double a, double b)
{
    if (f(a) * f(b) >= 0) {
        printf("Условие на сходимость не выполнено\n");
        return -1;
    }
    printf("Условие на сходимость выполнено\n");
    return 0;
}

int convergence_condition_Newtons_method(double x)
{
    if (f(x) * f_hatch_hatch(x) <= 0) {
        printf("Условие на сходимость не выполнено при x = %.2f\n", x);
        return -1;
    }
    printf("Условие на сходимость выполнено при x = %.2f\n", x);
    return 0;
}

void bisection_method(double a, double b, double eps)
{
    double x;
    do {
        x = (a + b) / 2;
        if (f(a) * f(x) < 0) {
            a = a;
            b = x;
        } else {
            a = x;
            b = b;
        }
    } while (fabs(f(x)) >= eps);
    printf("Корень уравнения X = %.4lf\n", x);
}

void Newtons_method(double x, double eps)
{
    do {
        x = x - (f(x) / f_hatch(x));
    } while (fabs(f(x)) >= eps);
    printf("Корень уравнения X = %.4lf\n", x);
}

void chord_method(double a, double b, double eps)
{
    double x0 = a;
    double x1 = b;
    double x2;
    do {
        x2 = x1 - f(x1) * ((x1 - x0) / (f(x1) - f(x0)));
        x0 = x1;
        x1 = x2;
    } while (fabs(f(x2) - f(x1)) >= eps);
    printf("Корень уравнения X = %.4lf\n", x2);
}

int main()
{
    double a, b, eps;
    a = 1.8;
    b = 2.0;
    eps = 0.01;
    printf("Метод бисекций: \n");
    if (convergence_condition(a, b) == -1)
        return -1;
    bisection_method(a, b, eps);

    printf("\nМетод Ньютона: \n");
    double check1 = convergence_condition_Newtons_method(a);
    double check2 = convergence_condition_Newtons_method(b);
    if (check1 == check2)
        return -1;
    double x = (check1 < check2) ? b : a;
    Newtons_method(x, eps);

	printf("\nМетод  хорд: \n");
	if (convergence_condition(a, b) == -1)
        return -1;
    chord_method(a, b ,eps);
    return 0;
}