#include <stdio.h>

int main() {
   int n, i, j;
   scanf("%d", &n);
   n--;
   float x[n+1], a[n+1], h[n], A[n], l[n+1], u[n+1], z[n+1], c[n+1], b[n], d[n];
   for (i = 0; i < n+1; ++i)
   scanf("%f", &x[i]);

   for (i = 0; i < n+1; ++i)
   scanf("%f", &a[i]);

   for (i = 0; i <= n-1; ++i)
   h[i] = x[i+1] - x[i];

   for (i = 1; i <= n-1; ++i)
   A[i] = 3 * (a[i + 1] - a[i]) / h[i] - 3 * (a[i] - a[i-1]) / h[i-1];

   l[0] = 1;
   u[0] = 0;
   z[0] = 0;

   for (i = 1; i <= n-1; ++i){
      l[i] = 2 * (x[i+1] - x[i-1]) - h[i-1] * u[i-1];
      u[i] = h[i] / l[i];
      z[i] = (A[i] - h[i-1] * z[i-1]) / l[i];
   }

   l[n] = 1;
   z[n] = 0;
   c[n] = 0;

   for (j = n-1; j >= 0; --j){
      c[j] = z[j] - u[j] * c[j + 1];
      b[j] = (a[j+1] - a[j]) / h[j] - h[j] * (c[j+1] + 2 * c[j]) / 3;
      d[j] = (c[j+1] - c[j]) / (3 * h[j]);
   }

   printf("%2s %8s %8s %8s %8s\n", "i", "ai", "ai", "ai", "di");
   for (i = 0; i < n; ++i)
   printf("%2d %8.2f %8.2f %8.2f %8.2f %8.2f\n", i, a[i], b[i], c[i], d[i]);
   return 0;
}
