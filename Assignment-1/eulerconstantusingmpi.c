#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define N 10

double facto(int x)
{
    double res = 1.0;
    for (int y = x; y >= 1; y--)
        res *= y;
    return res;
}

int main()
{

    MPI_Init(NULL, NULL);
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    double local_sum = 0.0;
    int part = N / world_size;
    int start_index = part * world_rank;
    int i;
    double f = 1.0;
    for (i = start_index; i < (start_index + part); i++)
    {
        f = facto(i);
        local_sum += (double)1 / f;
    }

    printf("Partial Euler's number value for process %d - %0.15f\n", world_rank, local_sum);
    double global_sum;

    MPI_Reduce(&local_sum, &global_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (world_rank == 0)
    {

        printf("Final Euler's number value = %0.15f\n", global_sum);
        printf("\nName: Priyanshu Mohanty \n Reg. No.: 19BCE0700\n");
    }

    MPI_Finalize();

    return 0;
}
