# Known limitations

The verified Windows x64 routes are CrossCVHello, LoadResizeSave, and a basic FFmpeg video write/read check. The Pascal examples were built with Delphi 13.2 and Lazarus 4.8 with FPC 3.2.2.

The image examples do not cover every OpenCV module or platform. SparseToDense optical flow and `PctComputeSignature` have historical edge cases that still need separate checks. The HighGui results include two checks that confirmed only the availability of an entry point.

The bundled bridge includes OpenCV SVM support. The legacy libSVM entry points (`CreateSVMModel`, `DeleteSVMModel`, `ComputeScore`, and `TrainSVMModel`) remain available for ABI compatibility and return an error because libSVM is not linked.

BuildOpticalFlowPyramid returns the level-zero image through its single matrix output and reports the number of additional levels built. This interface does not expose the other images or their derivatives.

LsdDrawSegments uses the OpenCV line overlay style. Its Color argument is reserved. LineDetect uses the FastLineDetector algorithm and reserves the LogEps and DensityTh arguments. Use the dedicated detector interfaces for explicit algorithm settings.

EdgeBoxesGetBoundingBoxes and SelectiveSearchProcess take the rectangle capacity in Count^ when a buffer is provided. Pass a nil buffer to query the required count. A short buffer stays unchanged and the bridge reports an error and the required count.

See [BUILD.md](BUILD.md) for the native library and [third-party notices](THIRD-PARTY-NOTICES.md) for build options and corresponding source.
