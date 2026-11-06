# Example checks

Build and run CrossCVHello and LoadResizeSave in Delphi 13.2 or Lazarus 4.8 for Windows x64. See [INSTALL.md](INSTALL.md).

- CrossCVHello prints the loaded bridge path, a pixel sum of 84, and 12 nonzero pixels.
- LoadResizeSave opens a chosen image and saves a 640 × 480 PNG. Open the result in an image viewer to verify its dimensions.
- The native video smoke test used the FFmpeg backend to write and read a test file. The corresponding-source asset describes how to rebuild with a modified FFmpeg.

These checks cover the named example routes. See [known limitations](KNOWN-ISSUES.md) for other bindings and platforms.
