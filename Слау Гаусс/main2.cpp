#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

void print(float** MTRX, int N);
float** create(int N);
float** create_rand(int N);
void m_Gauss(float** MTRX, int N);
int m_modif_Gauss(float** MTRX, int N);
void answer(float* T_MTRX);
void answer_2(float* T_MTRX, int N);
int rank_mtrx(int N, float** MTRX);

int main()
{
    int n, c;
    float** mtrx;
    cout << "Введите количество уравнений n = ";
    cin >> n;
    cout << "Заполнение матрицы. Случайным образом(0)/Собственноручно(1)" << endl << "->";
    cin >> c;
    if (c == 0)
        mtrx = create_rand(n);
    else
        mtrx = create(n);

    cout << endl << "Ваша матрица:" << endl;
    print(mtrx, n);

    int rank = rank_mtrx(n,mtrx);
    cout << endl << "Rank = " << rank << endl;
    if (rank < n)
    {
        cout << "The system has infinitely many solutions!" << endl;
        return 0;
    }

    cout << "Какой метод применять для решения? Простой(0)/Модифицированный(1)" << endl << "->";
    cin >> c;
    if (c == 0)
        m_Gauss(mtrx, n);
    else
        m_modif_Gauss(mtrx, n);

    return 0;
}

void print(float** MTRX, int N)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N + 1; j++)
        {
            if (j < N)
                cout << setw(10) << round(MTRX[i][j]*100)/100;
            else
                cout << setw(10) << "|" << round(MTRX[i][j] * 100) / 100;
        }
        cout << endl;
    }
}

float** create(int N)
{
    float** MTRX = new float* [N];
    for (int i = 0; i < N; i++)
    {
        MTRX[i] = new float[N + 1];
    }

    cout << endl << "Введите элементы матрицы:" << endl;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N + 1; j++)
        {
            cin >> MTRX[i][j];
        }
    return MTRX;
}

float** create_rand(int N)
{
    float** MTRX = new float* [N];
    for (int i = 0; i < N; i++)
    {
        MTRX[i] = new float[N + 1];
    }
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N + 1; j++)
        {
            MTRX[i][j] = rand() % 10;
        }
    return MTRX;
}

void m_Gauss(float** MTRX, int N)
{
    for (int i = 0; i < N; i++)
    {
        float t = MTRX[i][i];
        for (int j = i; j <= N; j++)
            MTRX[i][j] = MTRX[i][j] / t;
        for (int j = i + 1; j < N; j++)
        {
            t = MTRX[j][i];
            for (int k = i; k <= N; k++)
                MTRX[j][k] = MTRX[j][k] - t * MTRX[i][k];
        }
        cout << i+1 << ":" << endl;
        print(MTRX, N);
    }

    cout << endl << "Решенная матрица. Простой метод:" << endl;
    print(MTRX, N);

    /*Находим неизвестные переменные*/
    float* t_MATRX = new float[N];
    t_MATRX[N - 1] = MTRX[N - 1][N];
    for (int i = N - 2; i >= 0; i--)
    {
        t_MATRX[i] = MTRX[i][N];
        for (int j = i + 1; j < N; j++)
        {
            t_MATRX[i] = t_MATRX[i] - MTRX[i][j] * t_MATRX[j];
        }
    }

    answer(t_MATRX);
}

int m_modif_Gauss(float** MTRX, int N)
{
    float t, max = 0;
    int i_max = 0;
    for (int i = 0; i < N; i++)
    {
        if (abs(MTRX[i][0]) > max)
        {
            max = abs(MTRX[i][0]);
            i_max = i;
        }
    }
    if (i_max > 0)
    {
        for (int i = 0; i <= N; i++)
        {
            t = MTRX[0][i];
            MTRX[0][i] = MTRX[i_max][i];
            MTRX[i_max][i] = t;
        }
    }
    cout << endl;  print(MTRX, N);

    for (int i = N; i >= 0; i--)
    {
        MTRX[0][i] /= MTRX[0][0];
    }
    for (int i = 1; i < N; i++)
    {
        for (int j = N; j >= 0; j--)
        {
            MTRX[i][j] -= MTRX[i][0] * MTRX[0][j];
        }
    }
    cout << endl;  print(MTRX, N);

    for (int i = N; i > 0; i--)
    {
        MTRX[1][i] /= MTRX[1][1];
    }
    for (int i = 0; i < N; i++)
    {
        for (int j = N; j > 0; j--)
        {
            if (i != 1)
            {
                MTRX[i][j] -= MTRX[i][1] * MTRX[1][j];
            }
        }
    }

    for (int i = N; i > 1; i--)
    {
        MTRX[2][i] /= MTRX[2][2];
    }
    for (int i = 0; i < N - 1; i++)
    {
        for (int j = N; j > 1; j--)
        {
            MTRX[i][j] -= MTRX[i][2] * MTRX[2][j];
        }
    }

    cout << endl << "Решенная матрица. Модифицированный метод:" << endl;
    print(MTRX, N);

    float* t_MATRX = new float[N];
    for (int i = 0; i < N; i++)
        t_MATRX[i] = MTRX[i][N];

    answer(t_MATRX);
    return 0;
}

void answer(float* T_MTRX)
{
    cout << "Ответ: " << endl;
    cout << "x = " << round(T_MTRX[0]*100)/100 << endl;
    cout << "y = " << round(T_MTRX[1] * 100) / 100 << endl;
    cout << "z = " << round(T_MTRX[2] * 100) / 100 << endl;
}

void answer_2(float* T_MTRX, int N)
{
    for (int i = 0; i < N; i++)
    {
        cout << "x" << i + 1 << " = " << T_MTRX[i] << endl;
    }
}

int rank_mtrx(int N, float** MTRX) {
    float** MTRX_2 = new float* [N];
    for (int i = 0; i < N; i++)
    {
        MTRX_2[i] = new float[N + 1];
    }
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N + 1; j++)
        {
            MTRX_2[i][j] = MTRX[i][j];
        }
    int rank = N;
    int max = MTRX_2[0][0];
    for (int j = 0; j <= N; j++)
    {
        for (int i = 0; i < N; i++)
            if (MTRX_2[i][j] > max)
                max = MTRX_2[i][j];
        if (abs(max) == 0) rank--;
    }

    for (int i = 0; i < N; i++)
    {
        float t = MTRX_2[i][i];
        for (int j = i; j <= N; j++)
            MTRX_2[i][j] = MTRX_2[i][j] / t;
        for (int j = i + 1; j < N; j++)
        {
            t = MTRX_2[j][i];
            for (int k = i; k <= N; k++)
                MTRX_2[j][k] = MTRX_2[j][k] - t * MTRX_2[i][k];
        }
    }
    int j;
    for (int i = 0; i < N; i++)
    {
        for (j = i + 1; j < N && !MTRX_2[i][j]; j++);
        if (j == N + 1) rank--;
    }


    return rank;
}
