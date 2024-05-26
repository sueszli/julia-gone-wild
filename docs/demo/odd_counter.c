#include <stdio.h>
#include <stdlib.h>
#include <omp.h>


static int omp_odd_counter(int *a, int n) {
    int i;
    int count_odd = 0;
    int my_count_odd = 0;

    // #pragma omp parallel for shared(a) private(my_count_odd)
    // for(i=0; i<n; i++) {
    //     if( a[i] % 2 == 1 ) {
    //         my_count_odd++;
    //     }
    // }

    // #pragma omp critical
    // count_odd += my_count_odd;

    return count_odd;
}

int main() {
    int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int n = sizeof(a) / sizeof(a[0]);
    printf("output: %d\n", omp_odd_counter(a, n));
    return EXIT_SUCCESS;
}
