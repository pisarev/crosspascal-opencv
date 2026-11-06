# Build and run the first OpenCV example

Extract this project and its matching native source asset. Follow [the build guide](BUILD.md) to produce `bin/crosscv.dll`. The examples use the DLL from that directory and need no global installation.

1. Open `examples/CrossCVHello.dproj` in Delphi 13.2 or `examples/CrossCVHello.lpi` in Lazarus 4.8 with FPC 3.2.2.
2. Build for Windows x64 and run the example. Its project file supplies the unit search paths.
3. The console prints the loaded bridge path and ABI, a pixel sum of 84, 12 nonzero pixels, and `CROSSCV_HELLO_PASS`. Press Enter to close it.

For a graphical example, open `examples/LoadResizeSave.dproj` or `examples/LoadResizeSave.lpi` in the same way. Select an image in the Open dialog. Choose where to save the resized PNG. The example prints the output path and saves a 640 × 480 image.

If a Pascal unit is missing, make sure `pascal` and `examples` are in the same repository folder. If the bridge cannot load, check that `bin/crosscv.dll` exists and that the example is built for Windows x64.
