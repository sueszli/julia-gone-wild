compile latex:

```bash
brew install --verbose --debug mactex

pdflatex -interaction=nonstopmode -output-directory=./docs ./docs/bopc_report.tex
```

working on the hydra cluster:

- delete `CMakeCache.txt`
- create the binary on the host platform
- give ./bin exec permissions
