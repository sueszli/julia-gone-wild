# development

_compiling latex_:

```bash
brew install --verbose --debug mactex

pdflatex -interaction=nonstopmode -output-directory=./docs ./docs/bopc_report.tex
```

_installing openmp_:

see: https://stackoverflow.com/a/29109926/13045051

see: https://mac.r-project.org/openmp/

```bash
xcode-select --install
brew install llvm libomp cmake gcc
gcc --version # ignore this version, v15 didn't work for me
brew list --versions gcc # this is the right one

gcc-14 -fopenmp -o ./demo/test ./demo/test.c && ./demo/test && rm -rf ./demo/test
```

_working on the hydra cluster_:

-   create the binary on the host platform - unless you're sure to have the same architecture as the cluster
-   delete `CMakeCache.txt`
-   give `./bin` exec permissions
