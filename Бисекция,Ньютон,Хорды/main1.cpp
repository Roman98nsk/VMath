#include <iostream>
#include <cmath>
using namespace std;

float f(float X);
float df(float X);
float bissec(float X_L, float X_R, float E);
float Newton(float X_L, float X_R, float E);
float hord(float X_L, float X_R, float E);


int main()
{
    float x_l, x_r, e, x = 0;
    int c;
    cout << "Enter the segment:\nX_left = "; cin >> x_l;
    cout << "X_right = "; cin >> x_r;
    cout << "Enter the E:\tE = "; cin >> e;
    cout << "Select a method: Bisection(0), Newton(1), Hord(2)\n->";
    cin >> c;
    switch (c)
    {
    case 0:
        x = bissec(x_l, x_r, e);
        break;
    case 1:
        x = Newton(x_l, x_r, e);
        break;
    case 2:
        x = hord(x_l, x_r, e);
        break;
    }
    cout << "\n\nAnswer: X = " << round(x * 1000) / 1000;

    return 0;
}

float f(float X)
{
    return pow(X, 2) - cos(X) + X;
}

float df(float X)
{
    return 2 * X + sin(X) + 1;
}

float bissec(float X_L, float X_R, float E)
{
    float X = 0;
    int c;
    if (f(X_L) * f(X_R) < 0)
    {
        cout << "The convergence condition is met!\n";
        c = 0;
        while (1)
        {
            X = (X_L + X_R) / 2;
            c++;
            if (fabs(f(X)) < E) break;
            if (f(X_L) * f(X) < 0) X_R = X;
            else X_L = X;
            cout << "\nIteration " << c << ":\tx_left = " << round(X_L * 1000) / 1000 << "\tx_right = " << round(X_R * 1000) / 1000;
        }
    }
    else cout << "The convergence condition is not met!\n";

    return X;
}

float Newton(float X_L, float X_R, float E)
{
    float X = 0;
    int c = 0;
    if (f(X_L) * f(X_R) < 0)
    {
        cout << "The convergence condition is met for X = X_left!\n";
        X = X_L;
    }
    else
    {
        if (f(X_L) * f(X_R) > 0)
        {
            cout << "The convergence condition is met for X = X_right!\n";
            X = X_R;
        }
        else
        {
            cout << "The convergence condition is not met!\n";
            return 0;
        }
    }
    while (1)
    {
        X = X - f(X) / df(X);
        c++;
        if (fabs(f(X)) < E) break;
        cout << "\nIteration " << c << ":\tX = " << round(X * 1000) / 1000;
    }

    return X;
}

float hord(float X_L, float X_R, float E)
{
    int c = 0;
    while (fabs(f(X_R)) > E)
    {
        c++;
        X_L = X_R - ((X_R - X_L) * f(X_R)) / (f(X_R) - f(X_L));
        X_R = X_L - ((X_L - X_R) * f(X_L)) / (f(X_L) - f(X_R));
        cout << "\nIteration " << c << ":\tx_left = " << round(X_L * 1000) / 1000 << "\tx_right = " << round(X_R * 1000) / 1000;
    }

    return X_R;
}
