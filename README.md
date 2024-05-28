<!-- ![](./julia-openmp/contrib/input1.png) -->

</img src="./julia-openmp/contrib/input1.png" width="100" height="100" />

# development

_compiling latex_:

```bash
brew install --verbose --debug mactex

pdflatex -interaction=nonstopmode -output-directory=./docs ./docs/report.tex
```

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
