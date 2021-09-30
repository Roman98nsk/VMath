#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
#define N 1000

float f(float x)
{
    return pow(x,2);
}

float rectangle_left(float a, float b);
float rectangle_right(float a, float b);
float trapezoid(float a, float b);
float Simpson(float a, float b);
float Runge(float a, float b);

int main()
{
    float a, b;
    cout << "Enter a = "; cin >> a; cout << "Enter b = "; cin >> b;
    cout << "Method Rectangle_left\t" << rectangle_left(a, b);
    cout << "\nMethod Rectangle_right\t" << rectangle_right(a, b);
    cout << "\nMethod Trapezoid\t" << trapezoid(a, b);
    cout << "\nMethod Simpson\t\t" << Simpson(a, b);
    cout << "\nMethod Runge\t\t" << Runge(a, b) << "\n";

    return 0;
}

float rectangle_left(float a, float b)
{
    float s = 0;
    for (int i = 0; i < N; i++)
    {
        s += ((b - a) * f(a + (i * (b - a)) / N)) / N;
    }

    return s;
}

float rectangle_right(float a, float b)
{
    float s = 0;
    for (int i = 1; i <= N; i++)
    {
        s += ((b - a) * f(a + (i * (b - a)) / N)) / N;
    }

    return s;
}

float trapezoid(float a, float b)
{
    float s = f(a) + f(b);
    for (int i = 1; i < N; i++)
    {
        s += 2 * f(a + (i * (b - a)) / N);
    }
    s *= (b - a) /(2 * N);

    return s;
}

float Simpson(float a, float b)
{
    float s = f(a) + f(b);
    for (int i = 1; i < N; i++)
    {
        s += (2 + 2 * (i % 2)) * f(a + (i * (b - a)) / N);
    }
    s *= (b - a) / (3 * N);

    return s;
}

float Runge(float a, float b)
{
    float s = 0, h = (b - a)/N, k = a + h / 2;
    while (k <= b)
    {
        s += f(k) * h;
        k += h;
    }

    return s;
}
