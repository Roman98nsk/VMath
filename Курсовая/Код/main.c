#include <stdio.h>

double F (double x, double y)
{
  return x + y;
}


double eiler (double(*f)(double, double), double x0, double y0, double xn, double h) {

    double y = y0;

    for (double x = x0; x <= xn; x += h) {
    	y0 = y;
        y += h * f (x, y);
    }

    return y0;
}

double eiler_m (double(*f)(double, double), double x0, double y0, double xn, double h) {

    double y = y0;

    for (double x = x0; x <= xn; x += h) {
    	y0 = y;
        y += h * f (x + h / 2, y + h * f ( x , y ) / 2);
    }


    return y0;
}

double runge_kutt (double(*f)(double, double), double x0, double y0, double xn, double h) {

    double x, y = y0, k1 = 0, k2 = 0, k3 = 0, k4 = 0;

    for (x = x0; x <= xn; x += h) {
    	y0 = y;


        k1 = h * f ( x          , y );
        k2 = h * f ( x + h / 2. , y + k1 / 2. );
        k3 = h * f ( x + h / 2. , y + k2 / 2. );
        k4 = h * f ( x + h      , y + k3 );

        y += (k1 + 2.*k2 + 2.*k3 + k4) / 6.0;
    }

    return y0;
}

int main () {

    double x0 = 0. , y0 = 1. , xn = 10. , h = 0.01;

    double y = runge_kutt (F, x0, y0, xn, h);

    printf ("f( %f ) = %.4f; By Runge-Kutt of the 4th order method\n", xn, y);

    return 0;
}
