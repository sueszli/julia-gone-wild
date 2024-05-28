# Exercise 5

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
1100](./assets/juliap_job_1100.png)

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
16 cores](./assets/juliap2_job.png)

# Exercise 6

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
sizes](./assets/strong_scaling_plot.png)

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
sizes](./assets/weak_scaling_plot.png)

<!-- # Appendix

  schedule       n     p      time
  ------------ ------ ---- ----------
  static        1100   16   2.450491
  static        1100   16   2.448260
  static        1100   16   2.449136
  static,1      1100   16   2.448672
  static,1      1100   16   2.446850
  static,1      1100   16   2.446568
  dynamic,10    1100   16   2.447841
  dynamic,10    1100   16   2.447689
  dynamic,10    1100   16   2.453576
  guided,8      1100   16   2.447433
  guided,8      1100   16   2.447667
  guided,8      1100   16   2.446407

  : julia schedule -->
