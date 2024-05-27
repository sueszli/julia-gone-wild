/*
 * (C) 2021 Sascha Hunold
 */

#include <math.h>
#include "filter.h"

const int fwidth2  = 1;
const int fheight2 = 1;


void apply_filter(png_bytep *row_pointers, png_bytep *buf, int width, int height, double filter[3][3], int rounds) {
    int block_size = 64;
    for(int r=0; r<rounds; r++) {
        #pragma omp parallel
        {
            #pragma omp single
            {
                for(int i=fwidth2; i<width - fwidth2; i += block_size) {
                    for(int j=fheight2; j<height - fheight2; j += block_size) {
                        #pragma omp task firstprivate(i, j)
                        {
                            for(int bi = i; bi < i + block_size && bi < width - fwidth2; bi++) {
                                for(int bj = j; bj < j + block_size && bj < height - fheight2; bj++) {
                                    filter_on_pixel(row_pointers, buf, bi, bj, filter);
                                }
                            }
                        }
                    }
                }
             }
        }

	    // swap buffer with image
	    png_bytep *tmp = buf;
	    buf = row_pointers;
	    row_pointers = tmp;
    }
}
