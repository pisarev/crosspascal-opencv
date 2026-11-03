# CrossPascal OpenCV

`crosspascal-opencv` is the repository for the planned OpenCV package: Pascal bindings, a C++ bridge, and native dependencies.

The current preview contains documentation and a source inventory checker. Native package acceptance is still pending. This preview contains no binding source or bridge binaries. It does not establish ABI compatibility or provide a supported OpenCV installation.

The package will have its own build, license, and runtime checks. It can be released independently of Leptonica and the model converter.

From this repository's root, verify the documentation snapshot with Python 3.12 or later: `python -B scripts/verify_source.py`. The inventory allows declared root Git metadata and checks all distributed files.

The original documentation and utility use the [MIT license](LICENSE). This draft redistributes no OpenCV implementation.
