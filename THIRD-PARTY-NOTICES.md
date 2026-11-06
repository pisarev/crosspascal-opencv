# Third-party notices

Original CrossPascal Pascal bindings, the Mat helper, the C++ bridge and own documentation use the repository's [MIT license](LICENSE). Native dependencies keep their original copyright and license texts. The combined native DLL must not be described as a single-license MIT binary.

## Preserved native terms

| Component or material | Preserved notices |
| --- | --- |
| OpenCV 4.10.0 | [LICENSE](licenses/opencv/LICENSE), [COPYRIGHT](licenses/opencv/COPYRIGHT), and the license-change/historical texts under `licenses/opencv/doc/` |
| OpenCV contrib 4.10.0 | [LICENSE](licenses/opencv_contrib/LICENSE) and module-specific notices |
| FFmpeg 6.1.1 | [LICENSE.md](licenses/ffmpeg/LICENSE.md), [LGPL 2.1](licenses/ffmpeg/COPYING.LGPLv2.1) and the other preserved optional GPL/LGPL texts |
| dav1d 1.3.0 | [COPYING](licenses/dav1d/COPYING) |
| libavif 1.0.4 | [LICENSE](licenses/libavif/LICENSE) |
| Bundled native dependencies | Original notices under `licenses/opencv/3rdparty/` and `licenses/opencv/modules/`, plus the complete source archives |

[LICENSES.tsv](LICENSES.tsv) records the repository's collected notices. The companion source asset's `LICENSE-INDEX.json` records the preserved upstream notice files, including the landmark model's publisher notice; its full archives retain additional file-specific notices. A notice's inclusion does not establish that every optional upstream module was linked into the DLL.

This software is based in part on the work of the Independent JPEG Group.

## Static FFmpeg and corresponding sources

The recorded native recipe statically links FFmpeg into the OpenCV/CrossCV route. Its configure log identifies **LGPL version 2.1 or later**. The configure command does not include `--enable-gpl`, `--enable-version3` or `--enable-nonfree`; optional GPL source texts remain preserved in the complete archive.

The matching `opencv-windows-x64` source asset provides full FFmpeg, OpenCV/contrib and consuming bridge sources. It includes the portable build recipe, input hashes and `RELINKING.md` with a modified-FFmpeg rebuild/relink example. Precompiled relink objects are not supplied; the documented route recompiles the consuming source. See [BUILD.md](BUILD.md) for the asset identity and entry points. A portable rebuild and a separate modified-FFmpeg rebuild were checked on Windows x64.

The retained OpenCV setting **`OPENCV_ENABLE_NONFREE=ON`** is a separate configuration choice. This notice does not claim patent or legal clearance.

## Build environment and additional inputs

The six exact cache inputs are attributed in [CACHE-INPUT-TERMS.md](CACHE-INPUT-TERMS.md): ADE under Apache 2.0, the landmark model under its publisher's BSD 3-Clause terms, and four WeChat QRCode files under the publisher's Apache 2.0 terms. The landmark model's [original README and BSD notice](licenses/opencv_3rdparty/face_landmark/README.md) is included unchanged. These attributions identify the supplied bytes and do not assert model quality.

Compiler/runtime provenance and exact source-acquisition instructions are recorded in the source asset's `TOOLCHAIN-SOURCES.md` and package lock. Compiler packages and OCI layers are obtained separately. The source asset records the inputs for building the runtime on your machine.
