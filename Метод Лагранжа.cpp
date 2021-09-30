#include <iostream>
#include <iomanip>
using namespace std;
#define N 4

float f(float x)
{
    return x * x;
}

void print(float X[N], float Y[N]);
float lagranz(float x[N], float y[N], float X);
float aitken(float x[N], float y[N], float X);
float newton(float x[N], float y[N], float X);

int main()
{
    int c = 1;
    float x;
    float X[N] = { 1, 2, 3, 4 };
    float Y[N];
    for (int i = 0; i < N; i++)
    {
        Y[i] = f(X[i]);
    }
    print(X, Y);

    cout << "\n\nEnter the value of the X point:\nX = ";
    cin >> x;

    while (c)
    {
        cout << "\nSelect a method: Lagranz(1), Aitken(2), Newton(3), the end(0)\n->";
        cin >> c;
        switch (c)
        {
        case 0:
            break;
        case 1:
            cout << "\nMethos Lagranz\n\t\tAnswer:\tP(" << x << ") = " << lagranz(X, Y, x) << "\n\n";
            break;
        case 2:
          //  cout << "\nMethos Aitken\n\t\tAnswer:\tP(" << x << ") = " << aitken(X, Y, x) << "\n\n";
            break;
        case 3:
            cout << "\nMethos Newton\n\t\tAnswer:\tP(" << x << ") = " << newton(X, Y, x) << "\n\n";
            break;
        }
    }

    return 0;
}

void print(float X[N], float Y[N])
{
    cout << "Table:\nX|";
    for (int i = 0; i < N; i++)
    {
        cout << setw(10) << X[i];
    }
    cout << "\nY|";
    for (int i = 0; i < N; i++)
    {
        cout << setw(10) << Y[i];
    }
}

float lagranz(float x[N], float y[N], float X)
{
    float answer = 0, ch, zn;
    for (int j = 0; j < N; j++) {
        ch = 1; zn = 1;
        for (int i = 0; i < N; i++) {
            if (i != j)
            {
                ch *= (X - x[i]);
                zn *= (x[j] - x[i]);
            }
        }
        answer += y[j] * ch / zn;
    }

    return answer;
}

float aitken(float x[N], float y[N], float X)
{
    float P[N];
    for (int i = 0; i < N; i++)
    {
        P[i] = y[i];
    }

    for (int k = 1; k < N; k++)
    {
        for (int i = 0; i < N - k; i++)
        {
            P[i] = (P[i] * (x[i + k] - X) - P[i + 1] * (x[i] - X)) / (x[i + k] - x[i]);
        }
        P[N - k] = 0;
    }

    return P[0];
}

float newton(float x[N], float y[N], float X)
{
    float answer = y[0], a, h;
    for (int i = 1; i < N; i++)
    {
        a = 0;
        for (int j = 0; j <= i; j++)
        {
            h = 1;
            for (int k = 0; k <= i; k++)
            {
                if (k != j)
                    h *= (x[j] - x[k]);
            }
            a += y[j] / h;
        }
        for (int j = 0; j < i; j++)
            a *= (X - x[j]);
        answer += a;
    }
    return answer;
}
