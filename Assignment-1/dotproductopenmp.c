#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <string.h>
#include <time.h>

#define SIZ 15
int main(int argc, char *argv[])
{
    float a[SIZ], b[SIZ], dotprod, dpp;
    int i, tid;
    dotprod = 0.0;
    for (i = 0; i < SIZ; i++)
    {
        a[i] = 1.0 * (i + 1);
        b[i] = 1.0 * (i + 2);
    }
    printf("PRIYANSHU MOHANTY 19BCE0700\n");
    printf("\n Values of a and b :\n");
    for (i = 0; i < SIZ; i++)
    {
        printf(" a[%d]= %.1f\t b[%d]= %.1f\n", i, a[i], i, b[i]);
    }
    printf("\n");
#pragma omp parallel shared(a, b, dotprod, dpp) private(tid, i)
    {
        tid = omp_get_thread_num();
#pragma omp for private(i)
        for (i = 0; i < SIZ; i++)
        {
            dpp += a[i] * b[i];
            printf("thread: %d\n", tid);
        }
#pragma omp critical
        {
            dotprod = dpp;
            printf("thread %d\n", tid);
        }
    }
    printf("\n Dot Product = %f\n", dotprod);
}
