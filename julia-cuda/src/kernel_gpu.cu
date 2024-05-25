#include <iostream>
#include "kernel.hpp"
#include <cuda_runtime.h>

extern int global_block_x, global_block_y;

void julia_kernel(float *julia_set, Complex c, float scale, int res_x, int res_y, int max_iter, float max_mag, float x_scale, float y_scale) {

    // compute a good default block size
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int y = blockIdx.y * blockDim.y + threadIdx.y;

    // thread safety
    if (x >= res_x || y >= res_y) {
        return;
    }

    // calculate coordinates
    float scaledX = scale * x_scale * (float)(x - res_x / 2) / (res_x / 2);
    float scaledY = scale * y_scale * (float)(y - res_y / 2) / (res_y / 2);

    Complex z(scaledX, scaledY);

    int i = 0;
    for(i = 0; i < max_iter; i++) {
        z = z * z + c;
        if(z.magnitude2() > max_mag) {
            break;
        }
    }

    // calculate shade for julia set value
    float juliaShade = ((float)i) / max_iter;
    julia_set[y * res_x + x] = juliaShade; // note the swapped indices due to row-major order in memory
}

void launch_julia_kernel(float *d_julia_set, Complex c, float scale, int res_x, int res_y, int max_iter, float max_mag, float x_scale, float y_scale) {
    dim3 blockSize(16, 16); // example block size -> must be adjusted based on the GPU specs
    dim3 gridSize((res_x + blockSize.x - 1) / blockSize.x, (res_y + blockSize.y - 1) / blockSize.y);

    julia_kernel<<<gridSize, blockSize>>>(d_julia_set, c, scale, res_x, res_y, max_iter, max_mag, x_scale, y_scale);
}
