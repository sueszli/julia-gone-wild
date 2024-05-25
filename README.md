_compiling latex_:

```bash
brew install --verbose --debug mactex

pdflatex -interaction=nonstopmode -output-directory=./docs ./docs/bopc_report.tex
```

_working on the hydra cluster_:

- delete `CMakeCache.txt`
- create the binary on the host platform
- give ./bin exec permissions
