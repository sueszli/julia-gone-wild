#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argv[]) {
    int nprocs = omp_get_num_procs();
    printf("nprocs: %d\n", nprocs);
    
    int i = 0;
    int n = 17;
    int a[n];
    int t[nprocs];
    
    #pragma omp parallel for schedule(runtime)
    for (i=0; i<n; i++) {
        a[i] = omp_get_thread_num();
        t[omp_get_thread_num()]++;
        printf("a[%d] = %d\n", i, a[i]);
        printf("t[%d] = %d\n", omp_get_thread_num(), t[omp_get_thread_num()]);
    }
}
