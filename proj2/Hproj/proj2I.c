#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int *AllocateArray(int N)
{
    /* Allocate an array with N integers.
     * The value of each element of the array should be a
     * random number between 0 and 10N.
     * Hint: use the rand() function and a modulo operator.
     */
    int *result = malloc(N * sizeof(int));
    for (int i=0; i<N; i++){
        result[i] = rand() % (10*N + 1);
    }
    return result;
}

void SortArray(int *A, int N)
{
    int diff(const void* a, const void*  b){
        return (*(int*)a - *(int*)b);
    }
    qsort(A, N, sizeof(int), diff);
}

void DeallocateArray(int *A)
{
    free(A);
}

int main()
{
//    int sizes[8] = { 1000, 2000, 4000, 8000, 16000, 32000, 64000, 128000 };


// For fun:
  int sizes[11] = { 1000, 2000, 4000, 8000, 16000, 32000, 64000, 128000,
                    256000, 512000, 1024000 }; 
 

    for (int i = 0 ; i < 11 ; i++)
    {
        double alloc_time = 0., sort_time = 0., dealloc_time = 0.;
        struct timeval startTime;
        struct timeval endTime;

        // Call the three functions in a sequence. Also use
        // gettimeofday calls surrounding each function and set the 
        // corresponding variable (alloc_time, sort_time, dealloc_time).
        gettimeofday(&startTime, NULL);
        int *A = AllocateArray(sizes[i]);
        gettimeofday(&endTime, NULL);

        alloc_time = (endTime.tv_usec - startTime.tv_usec) * 0.000001;

        gettimeofday(&startTime, NULL);
        SortArray(A, sizes[i]);
        gettimeofday(&endTime, NULL);

        sort_time = endTime.tv_sec - startTime.tv_sec + (endTime.tv_usec-startTime.tv_usec)*0.000001;

        gettimeofday(&startTime, NULL);
        DeallocateArray(A);
        gettimeofday(&endTime, NULL);

        dealloc_time = (endTime.tv_usec - startTime.tv_usec) * 0.000001;

        printf("Timings for array of size %d\n", sizes[i]);
        printf("\tTime for allocation is %g, time per element = %g\n", alloc_time, alloc_time/sizes[i]);
        printf("\tTime for sort_time is %g, time per element = %g\n", sort_time, sort_time/sizes[i]);
        printf("\tTime for deallocation is %g\n", dealloc_time);
    }
}
