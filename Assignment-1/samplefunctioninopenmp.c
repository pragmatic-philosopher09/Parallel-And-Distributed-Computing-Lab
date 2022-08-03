#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

omp_nest_lock_t my_lock;

void Test()
{
    int tid = omp_get_thread_num();
    omp_set_nest_lock(&my_lock);
    printf("Thread %d - starting nested locked region\n", tid);
    printf("Thread %d - ending nested locked region\n", tid);
    omp_unset_nest_lock(&my_lock);
}

int main(int argc, char *argv[])
{
    int nthreads, tid, procs, maxt, inpar, dynamic, nested;
    double timespent, ptime;
    /* Start parallel region */
#pragma omp parallel num_threads(100) private(nthreads, tid)
    {
        /* Obtain thread number */
        tid = omp_get_thread_num(); /* Only master thread does this */
                                    /* Get environment information */

        omp_set_num_threads(69);
        omp_set_dynamic(12);

        procs = omp_get_num_procs();
        nthreads = omp_get_num_threads();
        maxt = omp_get_max_threads();
        inpar = omp_in_parallel();
        dynamic = omp_get_dynamic();
        nested = omp_get_nested();
        timespent = omp_get_wtime();
        ptime = omp_get_wtick();

        if (tid % 24 == 0)
        {
            printf("Thread %d getting environment info...\n", tid);

            /* Print environment information */
            printf("Number of processors = %d\n", procs);
            printf("Number of threads = %d\n", nthreads);
            printf("Max threads = %d\n", maxt);
            printf("In parallel? = %d\n", inpar);
            printf("Dynamic threads enabled? = %d\n", dynamic);
            printf("Nested parallelism supported? = %d\n", nested);
            printf("Elapsed Wall Clock Time ==> %f\n", timespent);
            printf("Seconds Between Clock Ticks ==> %f\n", ptime);
        }
    }

    omp_init_nest_lock(&my_lock);

#pragma omp parallel num_threads(4)
    {
        int i, j;

        for (i = 0; i < 5; ++i)
        {
            omp_set_nest_lock(&my_lock);
            if (i % 3)
                Test();
            omp_unset_nest_lock(&my_lock);
        }
    }

    omp_destroy_nest_lock(&my_lock);

    return 0;
}
