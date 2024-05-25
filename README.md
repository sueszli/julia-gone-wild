<!-- julia gone openmp -->

_compiling latex_:

```bash
brew install --verbose --debug mactex

pdflatex -interaction=nonstopmode -output-directory=./docs ./docs/bopc_report.tex
```

_working on the hydra cluster_:

-   create the binary on the host platform - unless you're sure to have the same architecture as the cluster
-   delete `CMakeCache.txt`
-   give `./bin` exec permissions
