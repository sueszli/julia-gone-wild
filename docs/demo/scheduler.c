#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argv[]) {
    int n_threads = omp_get_num_procs();
    n_threads = 4;

    // #pragma omp parallel num_threads(n_threads)
    // {
    //     printf("child id: %d\n", omp_get_thread_num());
    // }
    #pragma omp parallel for schedule(runtime)
    for (i=0; i<n; i++) {
        a[i] = omp_get_thread_num();
        t[omp_get_thread_num()]++;
    }
}

