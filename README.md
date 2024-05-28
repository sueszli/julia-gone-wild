parallel computing of julia fractals ✨

<img src="./julia-openmp/contrib/input1.png" width="300" height="300" />

<br><br><br>

# openmp benchmark results

## Parallelize the pixel computation

The `for` is used to parallelize the loops and needs to be called inside
parallel blocks to be effective which explains the
`#pragma omp parallel for`. In order to guarantee a canonical form `i`
and `j` are set to private variables. Setting `nit` and `z` to `private`
ensures that each thread has its own instance of these variables so that
there are no errors in the computation. Since the remaining variables
are constants, there is no need for synchronization. Lastly, a
`collapse(2)` allows the nested loops to be treated as a single loop,
which can improve parallel efficiency. This is only possible because
they are perfectly nested loops.

## Running time analysis

The plot shows that using more cores reduces
running time significantly up to 16 cores. From 1 to 4 cores, the
running time drops sharply, then continues to improve up to 16 cores.
Beyond 16 cores, the benefits decrease, and the running time stays
around 0.02 seconds. Adding more than 24 cores slightly increases the
running time, likely due to overhead. Overall, the program performs best
with up to 16 cores, with minimal gains and some overhead issues beyond
that.

![Minimum runnting time vs number of cores for an input size of
90](./assets/juliap_job_90.png)

When setting the input size to 1100,
figure reveals that the running time decreases
significantly up to 16 cores, similar to the n=90 case. Beyond 16 cores,
the running time continues to decrease but at a much slower rate, and
eventually stabilizes. Unlike the n=90 case, there is no noticeable
increase in running time when using more than 24 cores, suggesting that
the overhead is better managed or less impactful for larger workloads.
The larger problem size of n=1100 benefits more from parallelization, as
distributing the increased workload across multiple cores leads to more
substantial performance gains.

![Minimum running time vs number of cores for an input size of
1100](./docs/assets/juliap_job_1100.png)

## Influence of schedule parameter

The graph demonstrates minimal differences in running
times for different scheduling options with n=1100 and 16 cores. This
suggests that the workload is well-balanced across the cores regardless
of the schedule used which can also be confirmed by the previously
discussed figures. `Guided,8` performs slightly better
than `dynamic,10` , likely due to better adjustment of chunk sizes. Both
`static` and `static,1` schedules show similar performance, with
`static,1` marginally better. Overall, the uniform nature of the
workload leads to evenly distributed loads, making the scheduling
overhead negligible.

![Minimum running time vs schedule option for an input size of 1100 and
16 cores](./docs/assets/juliap2_job.png)

## Parallelize the filter computation

Again, the thread team is created with `#pragma omp parallel` and the
tasks are created inside the parallel section. Without `single` each
thread of the team would call `filter_on_pixel`. The private variables
are initialized with the value of the outside variable, by defining them
as `firstprivate` because otherwise all tasks created within the loop
would reference the same i and j variables. The task-based parallelism
would create a task for each pixel, which is why the block_size was
adapted and experimented with.

## Strong scaling analysis

The figure shows that for a fixed problem size
and varying the number of cores, the performance shows a clear trend
where smaller block sizes (like 16) result in significantly higher
running times as the number of cores increases. This sharp increase,
especially noticeable at 32 cores, suggests that block size 16 is not
well-suited for higher core counts. Larger block sizes (32 and 64)
maintain relatively low running times with a gradual increase,
indicating better parallel efficiency, likely due to reduced overhead
and better cache utilization. The optimal core range for block sizes 32
and 64 appears to be 16 to 24, where the running time is minimized.

![Minimum running time vs number of cores for r=1 and various block
sizes](./docs/assets/strong_scaling_plot.png)

## Weak scaling analysis

In the weak scaling scenario, where both the number of cores and problem
size increase proportionally, the running time should ideally remain
constant if the system scales perfectly. However, as
the figure shows, the running time increases
with a block size of 16 as there is a sharp increase indicating poor
scalability and higher overheads as the workload grows. On the other
hand, block sizes 32 and 64 exhibit much flatter curves, indicating
better workload distribution. As a result, they provide a more stable
and predictable performance across different core counts.

![Minimum running time vs number of cores for r=p and various block
sizes](./docs/assets/weak_scaling_plot.png)

| schedule   | n    | p   | time     |
| ---------- | ---- | --- | -------- |
| static     | 1100 | 16  | 2.450491 |
| static     | 1100 | 16  | 2.448260 |
| static     | 1100 | 16  | 2.449136 |
| static,1   | 1100 | 16  | 2.448672 |
| static,1   | 1100 | 16  | 2.446850 |
| static,1   | 1100 | 16  | 2.446568 |
| dynamic,10 | 1100 | 16  | 2.447841 |
| dynamic,10 | 1100 | 16  | 2.447689 |
| dynamic,10 | 1100 | 16  | 2.453576 |
| guided,8   | 1100 | 16  | 2.447433 |
| guided,8   | 1100 | 16  | 2.447667 |
| guided,8   | 1100 | 16  | 2.446407 |

# system specs

the system used for benchmarking was a hydra node with the following specs:

```plaintext
bopc23s9@hydra-head:~$ lscpu

Architecture:                    x86_64
CPU op-mode(s):                  32-bit, 64-bit
Byte Order:                      Little Endian
Address sizes:                   46 bits physical, 48 bits virtual
CPU(s):                          16
On-line CPU(s) list:             0-15
Thread(s) per core:              1
Core(s) per socket:              16
Socket(s):                       1
NUMA node(s):                    1
Vendor ID:                       GenuineIntel
CPU family:                      6
Model:                           85
Model name:                      Intel(R) Xeon(R) Gold 6130 CPU @ 2.10GHz
Stepping:                        4
CPU MHz:                         1000.151
CPU max MHz:                     3700.0000
CPU min MHz:                     1000.0000
BogoMIPS:                        4200.00
L1d cache:                       512 KiB
L1i cache:                       512 KiB
L2 cache:                        16 MiB
L3 cache:                        22 MiB
NUMA node0 CPU(s):               0-15
...
```

# development

_installing openmp_:

-   see: https://stackoverflow.com/a/29109926/13045051
-   see: https://mac.r-project.org/openmp/

```bash
xcode-select --install
brew install llvm libomp cmake gcc
gcc --version # ignore this version, v15 didn't work for me
brew list --versions gcc # this is the right one

filename="scheduler"
gcc-14 -fopenmp -o ./docs/demo/$filename ./docs/demo/$filename.c && ./docs/demo/$filename && rm -rf ./docs/demo/$filename
```

_executing SLURM jobs on the TU Wien hydra cluster_:

-   create the binary on the machine you want to run it on - otherwise the binary will be compiled for the wrong architecture. on arm64, make sure to compile with `cmake -DCMAKE_C_COMPILER=/opt/local/bin/gcc-mp-13` or similar.
-   delete `CMakeCache.txt`
-   give `./bin` exec permissions
