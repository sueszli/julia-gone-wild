#include <stdio.h>
#include <stdlib.h>
#include <omp.h>


static int omp_tasks(int v) {
    int a = 0, b = 0;
    if (v <= 2) {
        return 1;
    } else {
        #pragma omp task shared(a) // shared
        a = omp_tasks(v - 1);
        #pragma omp task shared(b) // shared
        b = omp_tasks(v - 2);
        #pragma omp taskwait
        return a + b;
    }
}

void main() {
    int res;
    #pragma omp parallel {
        #pragma omp single nowait // single nowait
        res = omp_tasks(5);
    }
    printf("res=%d\n", res);
    return EXIT_SUCCESS;
}
