#include <omp.h>
#include <stdio.h>
#define ARR_SIZE 100
int a[ARR_SIZE];

int main(int *argc, char *argv[])
{
    int i, tid, numt, sum = 0;
    double t1, t2;

    for (i = 0; i < ARR_SIZE; i++)
    {
        a[i] = rand() % 1000; // Generating random nos. betwixt 0 to 1000.
    }

    t1 = omp_get_wtime();

#pragma omp parallel default(shared) private(i, tid)

    {

        int from, to, psum = 0;

        tid = omp_get_thread_num();
        numt = omp_get_num_threads();
        from = (ARR_SIZE / numt) * tid;
        to = (ARR_SIZE / numt) * (tid + 1) - 1;

        if (tid == numt - 1)
            to = ARR_SIZE - 1;

#pragma omp for schedule(dynamic, 2)

        for (i = from; i <= to; i++)
            psum += a[i];

#pragma omp critical

        sum += psum;
    }
