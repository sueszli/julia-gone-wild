# openmp benchmark results

openmp has a bunch of nifty abstraction layers to parallelize code. you can reduce, collapse and schedule loops, create tasks and sections, and even use simd instructions. this project benchmarks the performance of different openmp parallelization strategies on a julia fractal computation.

runtimes:

![Minimum runtime vs number of cores for an input size of
90](./assets/juliap_job_90.png)

![Minimum runtime vs number of cores for an input size of
1100](./assets/juliap_job_1100.png)

different scheduling strategies:

![Minimum runtime vs schedule option for an input size of 1100 and
16 cores](./assets/juliap2_job.png)

strong scaling analysis:

![Minimum running time vs number of cores for r=1 and various block
sizes](./assets/strong_scaling_plot.png)

weak scaling analysis:

![Minimum running time vs number of cores for r=p and various block
sizes](./assets/weak_scaling_plot.png)

metrics:

_speedup_

-   what difference does parallelization make?
-   $S_a(n,p) = \frac{T_{\text{seq}}(n)}{T_{\text{par}}(n,p)}$ = absolute speedup
-   $S_r(n,p) = \frac{T_{\text{par}}(n, 1)}{T_{\text{par}}(n,p)}$ = relative speedup
-   where:
    -   $n$ = input size
    -   $p$ = number of processors
    -   $T_{\text{par}}(n,p)$ = parallel runtime
    -   $T_{\text{seq}}(n)$ = sequential runtime

_parallelization efficiency_

-   what difference does each processor make?
-   $E(n,p) = \frac{T_{\text{seq}}(n)}{p \cdot T_{\text{par}}(n,p)} = \frac{1}{p} \cdot S_a(n,p)$

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

